#include <SFML/Graphics/Rect.hpp>

#include <StraveEngine/Component/Animation/AnimationFlag.hpp>

#include <StraveEngine/Component/Animation/Animation.hpp>


namespace Strave
{
	AnimationFlag::AnimationFlag(Animation& animation) :
		m_Animation(&animation)
	{
		animation.m_UseDefaultAnimation = false;
		animation.m_CurrentFrameRect->top = animation.m_CurrentFrameRect->height * animation.m_CurrentAnimation;
	}

	AnimationFlag::~AnimationFlag()
	{
		m_Animation->m_UseDefaultAnimation = true;
		m_Animation->m_CurrentFrameRect->top = ANIM_INIT_FRAME_LOCATION;
	}

	void AnimationFlag::Fold(AnimationFlag*& flag)
	{
		delete flag;
		flag = NULL_PTR;

		// thread::ThreadPool::SendToMutex([&flag]() {
		//		delete flag;
		//		flag = NULL_PTR;
		// });
	}
}
