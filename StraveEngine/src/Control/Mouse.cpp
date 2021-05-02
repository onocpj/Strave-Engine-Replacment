#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <StraveEngine/Control/Mouse.hpp>

#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/System/Vector2.hpp>
#include <StraveEngine/System/Convert.hpp>
#include <StraveEngine/System/Window.hpp>
#include <StraveEngine/System/EngineClocks.hpp>
#include <StraveEngine/Entity/GameObject.hpp>
#include <StraveEngine/UI/UserInterface.hpp>
#include <StraveEngine/Component/Image.hpp>
#include <StraveEngine/Component/Transform.hpp>
#include <StraveEngine/Component/Mesh.hpp>
#include <StraveEngine/Element/Texture.hpp>

#include <iostream>


namespace Strave
{
	////////////////////////////////////////////////////////////
	/// Mouse states
	////////////////////////////////////////////////////////////
	float Mouse::DoubleClick::lapsedTime = UNDEF_FLOAT;
	bool Mouse::DoubleClick::active = UNDEF_BOOL;

	Object* Mouse::Click::clickedObject = UNDEF_PTR;
	bool Mouse::Click::active = UNDEF_BOOL;

	////////////////////////////////////////////////////////////
	/// Mouse
	////////////////////////////////////////////////////////////
	bool Mouse::IsButtonPressed(Mouse::Button button) 
	{
		return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
	}

	bool Mouse::IsButtonPressed(Mouse::Button button, const UserInterface& ui) 
	{
		if (Mouse::Hover(ui))
			if (sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button)))
				return true;

		return false;
	}

	bool Mouse::IsButtonPressed(Mouse::Button button, const GameObject& object)
	{
		if (Mouse::Hover(object))
			if (sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button)))
				return true;

		return false;
	}

	bool Mouse::Click(Mouse::Button button)
	{
		if (IsButtonPressed(button))
			return true;

		return false;
	}

	bool Mouse::Click(Mouse::Button button, const UserInterface& ui)
	{
		if (IsButtonPressed(button, ui))
			return true;

		return false;
	}

	bool Mouse::Click(Mouse::Button button, const GameObject& object)
	{
		if (IsButtonPressed(button, object))
			return true;

		return false;
	}

	bool Mouse::DoubleClick(Mouse::Button button)
	{
		if (Released(button) == true || Mouse::DoubleClick::active == true)
		{
			Mouse::DoubleClick::lapsedTime += EngineClocks::DeltaTime;
			Mouse::DoubleClick::active = true;

			if (Mouse::DoubleClick::lapsedTime <= MOUSE_DOUBLE_CLICK_DELAY)
			{
				if (IsButtonPressed(button))
				{
					Mouse::DoubleClick::lapsedTime = 0.0f;
					Mouse::DoubleClick::active = false;
					return true;
				}
			}
			else
			{
				Mouse::DoubleClick::lapsedTime = 0.0f;
				Mouse::DoubleClick::active = false;
			}
		}

		return false;
	}

	bool Mouse::DoubleClick(Mouse::Button button, const UserInterface& ui)
	{
		if (Released(button, ui) == true || Mouse::DoubleClick::active == true)
		{
			Mouse::DoubleClick::lapsedTime += EngineClocks::DeltaTime;
			Mouse::DoubleClick::active = true;

			if (Mouse::DoubleClick::lapsedTime <= MOUSE_DOUBLE_CLICK_DELAY)
			{
				if (IsButtonPressed(button, ui))
				{
					Mouse::DoubleClick::lapsedTime = 0.0f;
					Mouse::DoubleClick::active = false;
					return true;
				}
			}
			else
			{
				Mouse::DoubleClick::lapsedTime = 0.0f;
				Mouse::DoubleClick::active = false;
			}
		}

		return false;
	}

	bool Mouse::DoubleClick(Mouse::Button button, const GameObject& object)
	{
		if (Released(button, object) == true || Mouse::DoubleClick::active == true)
		{
			Mouse::DoubleClick::lapsedTime += EngineClocks::DeltaTime;
			Mouse::DoubleClick::active = true;

			if (Mouse::DoubleClick::lapsedTime <= MOUSE_DOUBLE_CLICK_DELAY)
			{
				if (IsButtonPressed(button, object))
				{
					Mouse::DoubleClick::lapsedTime = 0.0f;
					Mouse::DoubleClick::active = false;
					return true;
				}
			}
			else
			{
				Mouse::DoubleClick::lapsedTime = 0.0f;
				Mouse::DoubleClick::active = false;
			}
		}

		return false;
	}

	bool Mouse::DoubleClick(Mouse::Button button, float clickDelay)
	{
		if (Released(button) == true || Mouse::DoubleClick::active == true)
		{
			Mouse::DoubleClick::lapsedTime += EngineClocks::DeltaTime;
			Mouse::DoubleClick::active = true;

			if (Mouse::DoubleClick::lapsedTime <= clickDelay)
			{
				if (IsButtonPressed(button))
				{
					Mouse::DoubleClick::lapsedTime = 0.0f;
					Mouse::DoubleClick::active = false;
					return true;
				}
			}
			else
			{
				Mouse::DoubleClick::lapsedTime = 0.0f;
				Mouse::DoubleClick::active = false;
			}
		}

		return false;
	}

	bool Mouse::DoubleClick(Mouse::Button button, float clickDelay, const UserInterface& ui)
	{
		if (Released(button, ui) == true || Mouse::DoubleClick::active == true)
		{
			Mouse::DoubleClick::lapsedTime += EngineClocks::DeltaTime;
			Mouse::DoubleClick::active = true;

			if (Mouse::DoubleClick::lapsedTime <= clickDelay)
			{
				if (IsButtonPressed(button, ui))
				{
					Mouse::DoubleClick::lapsedTime = 0.0f;
					Mouse::DoubleClick::active = false;
					return true;
				}
			}
			else
			{
				Mouse::DoubleClick::lapsedTime = 0.0f;
				Mouse::DoubleClick::active = false;
			}
		}

		return false;
	}

	bool Mouse::DoubleClick(Mouse::Button button, float clickDelay, const GameObject& object)
	{
		if (Released(button, object) == true || Mouse::DoubleClick::active == true)
		{
			Mouse::DoubleClick::lapsedTime += EngineClocks::DeltaTime;
			Mouse::DoubleClick::active = true;

			if (Mouse::DoubleClick::lapsedTime <= clickDelay)
			{
				if (IsButtonPressed(button, object))
				{
					Mouse::DoubleClick::lapsedTime = 0.0f;
					Mouse::DoubleClick::active = false;
					return true;
				}
			}
			else
			{
				Mouse::DoubleClick::lapsedTime = 0.0f;
				Mouse::DoubleClick::active = false;
			}
		}

		return false;
	}

	bool Mouse::Released(Mouse::Button button)
	{
		if (IsButtonPressed(button) || Mouse::Click::active == true)
		{
			Mouse::Click::active = true;

			if (!IsButtonPressed(button))
			{
				Mouse::Click::active = false;
				return true;
			}
		}

		return false;
	}

	bool Mouse::Released(Mouse::Button button, const UserInterface& ui)
	{
		if (IsButtonPressed(button, ui) || Mouse::Click::active == true)
		{
			Mouse::Click::active = true;

			if (!IsButtonPressed(button, ui))
			{
				Mouse::Click::active = false;
				return true;
			}
		}

		return false;
	}

	bool Mouse::Released(Mouse::Button button, const GameObject& object)
	{
		if (IsButtonPressed(button, object) || Mouse::Click::active == true)
		{
			Mouse::Click::active = true;

			if (!IsButtonPressed(button, object))
			{
				Mouse::Click::active = false;
				return true;
			}
		}

		return false;
	}

	bool Mouse::Hold(Mouse::Button button)
	{
		if (IsButtonPressed(button))
			return true;

		return false;
	}

	bool Mouse::Hold(Mouse::Button button, const UserInterface& ui)
	{
		if (IsButtonPressed(button, ui))
			return true;

		return false;
	}

	bool Mouse::Hold(Mouse::Button button, const GameObject& object)
	{
		if (IsButtonPressed(button, object))
			return true;

		return false;
	}

	bool Mouse::Hover(const UserInterface& ui)
	{
		Transform& uiTransforms = ui.GetComponent<Transform>();
		Image& uiImage = ui.GetComponent<Image>();

		Vector2i t_MousePosition = Convert::ToVector2i(sf::Mouse::getPosition(Mouse::GetGameWindow()));

		if (t_MousePosition.x >= uiTransforms.GetPosition().x &&
			t_MousePosition.y >= uiTransforms.GetPosition().y) 
		{
			if (t_MousePosition.x <= uiTransforms.GetPosition().x + uiImage.GetNativeSize().x &&
				t_MousePosition.y <= uiTransforms.GetPosition().y + uiImage.GetNativeSize().y) 
			{
				return true;
			}
		}

		return false;
	}

	bool Mouse::Hover(const GameObject& object)
	{
		sf::RenderWindow& window = Mouse::GetGameWindow();
		Transform& objectTransforms = object.GetComponent<Transform>();

		Vector2i mousePosition = UNDEF_VECTOR2I;
		Vector2f translatedPosition = UNDEF_VECTOR2F;

		Vector2u objectTextureSize = Vector2u(
			object.GetComponent<Mesh>().GetTexture().getSize().x,
			object.GetComponent<Mesh>().GetTexture().getSize().y
		);
		Vector2f objectSpriteScale = Vector2f(
			object.GetComponent<Transform>().GetScale().x,
			object.GetComponent<Transform>().GetScale().y
		);
		Vector2f objectSpriteSize = Vector2f(
			(float)objectTextureSize.x * objectSpriteScale.x,
			(float)objectTextureSize.y * objectSpriteScale.y
		);

		mousePosition = Convert::ToVector2(sf::Mouse::getPosition(Mouse::GetGameWindow()));
		translatedPosition = Convert::ToVector2(window.mapPixelToCoords(sf::Vector2i(
			mousePosition.x, mousePosition.y
		)));																			

		if (translatedPosition.x >= objectTransforms.GetPosition().x &&
			translatedPosition.y >= objectTransforms.GetPosition().y) 
		{
			if (translatedPosition.x <= objectTransforms.GetPosition().x + objectSpriteSize.x &&
				translatedPosition.y <= objectTransforms.GetPosition().y + objectSpriteSize.y) 
			{
				return true;
			}
		}

		return false;
	}

	bool Mouse::Drag(UserInterface& ui)
	{
		Transform& uiTransforms = ui.GetComponent<Transform>();
		Image& uiImage = ui.GetComponent<Image>();

		Vector2i mousePosition = Convert::ToVector2(sf::Mouse::getPosition(Mouse::GetGameWindow()));

		uiTransforms.SetPosition(Vector2f(
			mousePosition.x - uiImage.GetNativeSize().x / 2,
			mousePosition.y - uiImage.GetNativeSize().y / 2
		));

		return true;
	}

	bool Mouse::Drag(GameObject& object)
	{
		sf::RenderWindow& window = Mouse::GetGameWindow();
		Vector2i mousePosition = Convert::ToVector2(sf::Mouse::getPosition(window));

		Vector2f oldObjectPosition = UNDEF_VECTOR2F;
		Vector2f newObjectPosition = UNDEF_VECTOR2F;
		Vector2f transformedPosition = UNDEF_VECTOR2F;

		Vector2u objectTextureSize = Vector2u(
			object.GetComponent<Mesh>().GetTexture().getSize().x,
			object.GetComponent<Mesh>().GetTexture().getSize().y
		);
		Vector2f objectSpriteScale = Vector2f(
			object.GetComponent<Transform>().GetScale().x,
			object.GetComponent<Transform>().GetScale().y
		);
		Vector2f objectSpriteSize = Vector2f(
			(float)objectTextureSize.x * objectSpriteScale.x,
			(float)objectTextureSize.y * objectSpriteScale.y
		);

		oldObjectPosition = object.GetComponent<Transform>().GetPosition();
		transformedPosition = Convert::ToVector2f(window.mapCoordsToPixel(
			sf::Vector2f(oldObjectPosition.x, oldObjectPosition.y)
		));

		newObjectPosition = Convert::ToVector2f(window.mapPixelToCoords(sf::Vector2i(
			mousePosition.x - objectSpriteSize.x / 2,
			mousePosition.y - objectSpriteSize.y / 2
		)));

		object.GetComponent<Transform>().SetPosition(newObjectPosition);

		return true;
	}

	sf::RenderWindow& Mouse::GetSceneWindow(void)
	{
		return *Window::s_SceneWindow->m_RenderWindow;
	}

	sf::RenderWindow& Mouse::GetGameWindow(void)
	{
		return *Window::s_GameWindow->m_RenderWindow;
	}
}
