#pragma once

#include <StraveEngine/System/UndefinedDataTypes.hpp>


#define ANIM_INIT_FRAME_LOCATION		UNDEF_UINT


namespace Strave
{
	class Animation;

	class AnimationFlag final
	{
	public:
		AnimationFlag(Animation& animation);
		AnimationFlag(AnimationFlag&) = delete;
		~AnimationFlag();

		inline static bool IsRised(AnimationFlag* flag) { return (flag != UNDEF_PTR ? true : false); }
		inline static AnimationFlag* Rise(Animation& animation) { return new AnimationFlag(animation); }
		static void Fold(AnimationFlag*& flag);

	private:
		Animation* m_Animation;
	};
}

