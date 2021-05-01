#pragma once

#include <StraveEngine/Component/Animation/Animation.hpp>
#include <StraveEngine/System/DataTypes.hpp>


namespace Strave
{
	template<Uint64 size> class AnimationMap
	{
	private:
		struct Composition
		{
			Uint16 animation;
			Animation::Constraints constraints;
		};

	public:
		AnimationMap();
		AnimationMap(AnimationMap& animationMap) = default;
		~AnimationMap();

	public:
		Composition* m_AnimationComposition;
	};
}

