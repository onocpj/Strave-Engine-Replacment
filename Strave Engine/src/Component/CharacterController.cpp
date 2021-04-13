#include <SFML/Graphics/Transformable.hpp>

#include <StraveEngine/Component/CharacterController.hpp>

#include <StraveEngine/Entity/GameObject.hpp>
#include <StraveEngine/Component/Transform.hpp>
#include <StraveEngine/Component/Mesh.hpp>
#include <StraveEngine/Element/Sprite.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/System/Convert.hpp>
#include <StraveEngine/System/Vector2.hpp>
#include <StraveEngine/System/Log.hpp>


namespace Strave
{
	CharacterController::CharacterController(GameObject* object) :
		IComponent(),
		m_GameObject(object)
	{}

	CharacterController::CharacterController(GameObject* object, std::string name) :
		IComponent(name),
		m_GameObject(object)
	{}

	CharacterController::CharacterController(const CharacterController& characterController) :
		IComponent(characterController)
	{
		m_GameObject = characterController.m_GameObject;
	}

	void CharacterController::Move(Input::Axis axis, float inputValue, Keyboard::Key key) const
	{
		Mesh* mesh = &m_GameObject->GetComponent<Mesh>();
		if (mesh != UNDEF_PTR)
		{
			Transform* transforms = &m_GameObject->GetComponent<Transform>();
			MeshType meshType = mesh->GetMeshType();

			if (Keyboard::IsKeyPressed(key))
			{
				if (axis == Input::Axis::Horizontal)
					mesh->GetSprite<Sprite>().move(Convert::ToVector2(Vector2f(inputValue, 0.0f)));

				if (axis == Input::Axis::Vertical)
					mesh->GetSprite<Sprite>().move(Convert::ToVector2(Vector2f(0.0f, inputValue)));

				Vector2f position = Convert::ToVector2f(mesh->GetSprite<Sprite>().getPosition());
				transforms->SetPosition(position);
			}

			return;
		}
		else
			SV_CORE_WARN("function Move from CharacterController: no object assigned to character controller");
	}

	void CharacterController::Move(Input::Axis axis, float inputValue) const
	{
		Mesh* mesh = &m_GameObject->GetComponent<Mesh>();
		if (mesh != UNDEF_PTR)
		{
			Transform* transforms = &m_GameObject->GetComponent<Transform>();
			MeshType meshType = mesh->GetMeshType();

			if (axis == Input::Axis::Horizontal)
				mesh->GetSprite<Sprite>().move(Convert::ToVector2(Vector2f(inputValue, 0.0f)));

			if (axis == Input::Axis::Vertical)
				mesh->GetSprite<Sprite>().move(Convert::ToVector2(Vector2f(0.0f, inputValue)));

			Vector2f position = Convert::ToVector2f(mesh->GetSprite<Sprite>().getPosition());
			transforms->SetPosition(position);

			return;
		}
		else
			SV_CORE_WARN("function Move from CharacterController: no object assigned to character controller");
	}
}