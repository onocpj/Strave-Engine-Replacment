#include "SFML/Window/Keyboard.hpp"

#include <StraveEngine/Control/Keyboard.hpp>


namespace Strave
{
	bool Keyboard::IsKeyPressed(Keyboard::Key key) 
	{
		return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
	}
}
