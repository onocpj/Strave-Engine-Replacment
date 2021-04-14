#include <SFML/Graphics/Rect.hpp>

#include <StraveEngine/Component/Animation/Animation.hpp>

#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/System/Convert.hpp>
#include <StraveEngine/System/EngineClocks.hpp>
#include <StraveEngine/System/Array.hpp>
#include <StraveEngine/System/ExceptionHandler.hpp>
#include <StraveEngine/Entity/GameObject.hpp>
#include <StraveEngine/Component/Animation/AnimationContainer.hpp>
#include <StraveEngine/Component/Animation/AnimationFlag.hpp>
#include <StraveEngine/Component/Mesh.hpp>
#include <StraveEngine/Element/Sprite.hpp>
#include <StraveEngine/Element/Texture.hpp>
#include <StraveEngine/Renderer/Renderer.hpp>


namespace Strave 
{
	Uint16 FindLargestColumnNumber(const Animation::Constraints*& constraints, Uint16 framesNum);
	Vector2u CorrectImageCount(const Vector2u& imageCount);

	////////////////////////////////////////////////////////////
	/// Animation
	////////////////////////////////////////////////////////////
	Animation::Animation(const Texture& texture, Uint16 animationNum, const Constraints constraints[], std::string name) :
		IComponent(name),
		m_KEY(ANIM_KEY_UNASSIGNED),
		m_AnimationState(UNDEF_PTR), 
		m_Constraints(UNDEF_PTR),
		m_GameObject(UNDEF_PTR), 
		m_AnimationTextureGrid(&texture),
		m_FrameCount(UNDEF_VECTOR2U),
		m_CurrentAnimation(ANIM_DEF_ANIM),
		m_CurrentFrame(UNDEF_INT32),
		m_AnimationNum(UNDEF_INT32), 
		m_ElapsedTime(UNDEF_FLOAT),
		m_FrameSwitchTime(UNDEF_FLOAT),
		m_UseDefaultAnimation(true)
	{
		Init(animationNum, constraints);
		ExceptionHandler::Handle(AnimationContainer::Insert(*this, this->m_KEY));
	}

	Animation::Animation(Animation& animation) :
		IComponent(animation.ToString()),
		m_KEY(ANIM_KEY_UNASSIGNED),
		m_AnimationState(animation.m_AnimationState),
		m_Constraints(animation.m_Constraints),
		m_GameObject(animation.m_GameObject),
		m_AnimationTextureGrid(animation.m_AnimationTextureGrid),
		m_FrameCount(animation.m_FrameCount),
		m_CurrentAnimation(ANIM_DEF_ANIM),
		m_CurrentFrame(animation.m_CurrentFrame),
		m_AnimationNum(UNDEF_UINT32),
		m_ElapsedTime(UNDEF_FLOAT),
		m_FrameSwitchTime(UNDEF_FLOAT),
		m_UseDefaultAnimation(animation.m_UseDefaultAnimation)
	{
		Init(animation.m_FrameCount.y, animation.m_Constraints);
		ExceptionHandler::Handle(AnimationContainer::Insert(*this, this->m_KEY));
	}

	Animation::~Animation() 
	{
		if(m_AnimationState != UNDEF_PTR)
			delete m_AnimationState;

		delete m_CurrentFrameRect;
		delete[] m_Constraints;
	}

	void Animation::Init(Uint16 animationNum, const Constraints constraints[])
	{
		m_CurrentFrameRect = new sf::IntRect();
		m_Constraints = new Constraints[animationNum];

		if (Array::CopyArray(constraints, m_Constraints, animationNum) == ERROR_TYPE)
			m_FrameCount = Vector2u(UNDEF_UINT, animationNum);
		else
			m_FrameCount = Vector2u((Uint32)FindLargestColumnNumber(constraints, animationNum), animationNum);

		Vector2u t_AnimationTextureSize = Convert::ToVector2u(m_AnimationTextureGrid->getSize());
		Vector2u t_CorrectImageCount = CorrectImageCount(m_FrameCount);

		m_CurrentFrameRect->width = t_AnimationTextureSize.x / t_CorrectImageCount.x;
		m_CurrentFrameRect->height = t_AnimationTextureSize.y / t_CorrectImageCount.y;
		m_FrameSwitchTime = (m_Constraints[ANIM_DEF_ANIM].animationTime / t_CorrectImageCount.x);
		m_AnimationNum = t_CorrectImageCount.y;
	}

	void Animation::LoadConstraints(const Constraints& constraints) 
	{
		m_FrameCount.x = constraints.frames;
		m_FrameSwitchTime = (constraints.animationTime / constraints.frames);
	}

	void Animation::Update(const GameObject& object) 
	{
		if (object.HaveAssignComponent<Animation>())
			object.GetComponent<Animation>().Update();
	}

	void Animation::Update(void) 
	{
		m_ElapsedTime += EngineClocks::DeltaTime;

		if (m_ElapsedTime >= m_FrameSwitchTime) {
			m_ElapsedTime -= m_FrameSwitchTime;
			m_CurrentFrame++;

			if (m_CurrentFrame >= m_FrameCount.x) {
				m_ElapsedTime = 0.0f;
				m_CurrentFrame = 0;

				if (!m_UseDefaultAnimation) {
					if (m_Constraints != UNDEF_PTR)
						Animation::LoadConstraints(m_Constraints[ANIM_DEF_ANIM]);

					m_CurrentAnimation = AssignDefaultAnimation();
					AnimationFlag::Fold(m_AnimationState);
				}
			}
		}

		m_CurrentFrameRect->left = m_CurrentFrameRect->width * m_CurrentFrame;
		m_GameObject->GetComponent<Mesh>().GetSprite<Sprite>().setTextureRect(*m_CurrentFrameRect);
	}

	void Animation::Animate(Uint16 animation) 
	{
		if (animation <= m_AnimationNum - 1) {
			if (!this->IsActive()) {
				if (!AnimationFlag::IsRised(m_AnimationState)) {
					if (m_Constraints != UNDEF_PTR)
						Animation::LoadConstraints(m_Constraints[animation]);

					this->SetActiveAnimation(animation);
					m_AnimationState = AnimationFlag::Rise(*this);
				}
			}
		}
	}

	void Animation::AssignObject(GameObject& object) 
	{
		m_GameObject = &object;

		object.GetComponent<Mesh>().UpdateTexture(*m_AnimationTextureGrid);

		if (!m_GameObject->HaveAssignComponent<Animation>()) {
			if (m_Constraints != UNDEF_PTR)
				Animation::LoadConstraints(m_Constraints[ANIM_DEF_ANIM]);

			return;
		}
		else 
			SV_CORE_INFO("function Animation::AssignTo(GameObject2D&): Object have alaready assigned animation");
	}

	void Animation::Stop(void) 
	{
		if (m_AnimationState != NULL_PTR) {
			if (m_Constraints != UNDEF_PTR)
				Animation::LoadConstraints(m_Constraints[ANIM_DEF_ANIM]);

			m_CurrentAnimation = AssignDefaultAnimation();
			AnimationFlag::Fold(m_AnimationState);
		}
	}

	////////////////////////////////////////////////////////////
	/// Functions
	////////////////////////////////////////////////////////////
	Uint16 FindLargestColumnNumber(const Animation::Constraints*& constraints, Uint16 framesNum)
	{
		Uint16 t_Largest = constraints[0].frames;

		for (Uint64 index = 0; index != framesNum; index++)
			if (constraints[index].frames > t_Largest)
				t_Largest = constraints[index].frames;

		return t_Largest;
	}

	Vector2u CorrectImageCount(const Vector2u& imageCount)
	{
		Vector2u t_ImageCount = imageCount;

		if (t_ImageCount.x < 1)
			t_ImageCount.x = 1;

		if (t_ImageCount.y < 1)
			t_ImageCount.y = 1;

		return t_ImageCount;
	}
}

