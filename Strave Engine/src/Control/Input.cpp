#include <StraveEngine/Control/Input.hpp>


namespace Strave
{
	float Input::GetAxisDirection(Input::Direction direction)
	{
		switch (direction)
		{
		case Input::Direction::Up: case Input::Direction::Left: return AXIS_MOVE_VAL * AXIS_MOVE_INVERT; break;
		case Input::Direction::Down: case Input::Direction::Right: return AXIS_MOVE_VAL; break;
		default: return AXIS_MOVE_VAL; break;
		}
	}
}
