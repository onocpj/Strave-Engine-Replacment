#pragma once

#include <StraveEngine/System/Vector2.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/Component/IComponent.hpp>


#define ANIM_KEY_UNASSIGNED			ERROR_TYPE

#define ANIM_DEF_ANIM_TIME			UNDEF_FLOAT
#define ANIM_DEF_ANIM				UNDEF_UINT
#define AINM_DEF_ANIM_CONSTRAINTS		{ ANIM_DEF_ANIM, ANIM_DEF_ANIM_TIME }


namespace sf
{
	template <typename T> class Rect;
	typedef Rect<int> IntRect;
}
namespace Strave
{
	class AnimationFlag;
	class GameObject;
	class Texture;
	class Renderer;

	typedef Texture AnimationTexture;

	class STRAVE_COMPONENT_API Animation final : public IComponent
	{
	private: 
		friend AnimationFlag;
		friend GameObject;
		friend Renderer;

	public:
		///
		/// \brief Represents number of columns and animation time to loop
		/// through those columns. Can be used to customize your animation grid 
		/// texture layout.
		/// 
		/// \param Body: { frames, animationTime }
		/// \param
		/// \param frames - Number of frames in one row (number of animation frames)
		/// \param animationTime - Time to loop through all frames. Animation length (in seconds)
		///
		struct Constraints
		{
			Uint16	frames;
			float	animationTime;
		};

	public:
		Animation(Texture& texture, Uint16 animationNum, const Constraints constraints[], std::string name = EMPTY_STR);
		Animation(Animation& animation);
		~Animation();

		inline ComponentType GetComponentType(void) const override final { return ComponentType::Animation; }
		inline const Uint64& GetKey(void) const { return m_KEY; }
		inline bool IsActive(Uint16 animation) const { return m_CurrentAnimation == animation ? true : false; }
		inline bool IsActive(void) const { return m_CurrentAnimation > (Uint16)ANIM_DEF_ANIM ? true : false; }
		void Animate(Uint16 animation = (Uint16)ANIM_DEF_ANIM);
		void Stop(void);

	private:
		void Init(Uint16 animationNum, const Constraints constraints[]);

		inline void SetActiveAnimation(Uint16 animation) { m_CurrentAnimation = animation; }
		inline const Uint16 AssignDefaultAnimation(void) { return (Uint16)ANIM_DEF_ANIM; }
		void LoadConstraints(const Constraints& constraints);
		void Update(void);

	protected:
		static void Update(const GameObject& go2d);
		void AssignObject(GameObject& object);

	private:
		Uint64		m_KEY;
		AnimationFlag*	m_AnimationState;
		Constraints*	m_Constraints;
		GameObject*	m_GameObject;
		const Texture*	m_AnimationTextureGrid;
		sf::IntRect*	m_CurrentFrameRect;
		Vector2u	m_FrameCount;
		Uint16		m_CurrentAnimation;
		Uint32		m_CurrentFrame;
		Uint32		m_AnimationNum;
		float		m_ElapsedTime;
		float		m_FrameSwitchTime;
		bool		m_UseDefaultAnimation;
	};
}
