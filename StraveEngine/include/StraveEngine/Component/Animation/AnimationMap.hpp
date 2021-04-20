#pragma once

#include <StraveEngine/Component/Animation/Animation.hpp>
#include <StraveEngine/System/DataTypes.hpp>


namespace Strave
{
	struct AnimationMap
	{
		Uint16 animation;
		Animation::Constraints constraints;
	};
}

