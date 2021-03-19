#include <StraveEngine/Element/Sprite.hpp>


namespace Strave
{
	Sprite::Sprite() :
		sf::Sprite(),
		ISprite()
	{

	}

	Sprite::Sprite(std::string name) :
		sf::Sprite(),
		ISprite(name)
	{

	}
}
