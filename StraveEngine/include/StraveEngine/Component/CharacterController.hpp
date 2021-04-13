#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/Component/IComponent.hpp>
#include <StraveEngine/Control/Keyboard.hpp>
#include <StraveEngine/Control/Input.hpp>

#include <string>


namespace Strave
{
	class GameObject;

	class STRAVE_COMPONENT_API CharacterController final : public IComponent
	{
	public:
		CharacterController(GameObject* object);
		CharacterController(GameObject* object, std::string name);
		~CharacterController() = default;
		CharacterController(const CharacterController&);

		inline ComponentType GetComponentType(void) const override final { return ComponentType::CharacterController; }
		void Move(Input::Axis axis, float inputValue, Keyboard::Key onKey) const;
		void Move(Input::Axis axis, float inputValue) const;

	private:
		GameObject* m_GameObject;
	};
}
