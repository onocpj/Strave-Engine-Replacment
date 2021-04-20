#pragma once

#include <StraveEngine/System/Export.hpp>


namespace Strave
{
	class UserInterface;
	class GameObject;

	class STRAVE_CONTROL_API Mouse abstract final 
	{
	public:
		enum class Button
		{
			Left = 0, 
			Right, 
			Middle, 
			Button1,
			Button2
		};
		enum class Wheel
		{
			Vertical = 0,
			Horizontal
		};

		static bool IsButtonPressed(Mouse::Button button);
		static bool IsButtonPressed(Mouse::Button button, const UserInterface& ui);
		static bool IsButtonPressed(Mouse::Button button, const GameObject& object);
		static bool Click(Mouse::Button button);
		static bool Click(Mouse::Button button, const UserInterface& ui);
		static bool Click(Mouse::Button button, const GameObject& object);
		static bool DoubleClick(Mouse::Button button);
		static bool DoubleClick(Mouse::Button button, const UserInterface& ui);
		static bool DoubleClick(Mouse::Button button, const GameObject& object);
		static bool DoubleClick(Mouse::Button button, float clickDelay);
		static bool DoubleClick(Mouse::Button button, float clickDelay, const UserInterface& ui);
		static bool DoubleClick(Mouse::Button button, float clickDelay, const GameObject& object);
		static bool Released(Mouse::Button button);
		static bool Released(Mouse::Button button, const UserInterface& ui);
		static bool Released(Mouse::Button button, const GameObject& object);
		static bool Hold(Mouse::Button button);
		static bool Hold(Mouse::Button button, const UserInterface& ui);
		static bool Hold(Mouse::Button button, const GameObject& object);
		static bool Hover(const UserInterface& ui);
		static bool Hover(const GameObject& object);
		static bool Drag(UserInterface& ui);
		static bool Drag(GameObject& object);
	};
}
