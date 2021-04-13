#pragma once

#include <StraveEngine/System/Export.hpp>


#define AXIS_MOVE_VAL		100.0f
#define AXIS_MOVE_INVERT	-1.0f


namespace Strave 
{
	class STRAVE_COMPONENT_API Input abstract final
	{
	public:
		enum class Direction
		{
			Up = 0,		// Axis: Y * (-1)
			Down,		// Axis: Y * 1
			Left,		// Axis: X * (-1)
			Right		// Axis: X * 1
		};
		enum class Axis
		{
			Horizontal = 0, // X Axis
			Vertical		// Y Axis
		};

	public:
		Input() = default;
		~Input() = default;
		Input(const Input&) = default;

		static float GetAxisDirection(Direction direction);
	};
}
