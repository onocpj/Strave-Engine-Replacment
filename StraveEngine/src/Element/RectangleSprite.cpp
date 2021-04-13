#include <StraveEngine/Element/RectangleSprite.hpp>


namespace Strave
{
	RectangleSprite::RectangleSprite() :
		sf::RectangleShape(),
		ISprite()
	{

	}

	RectangleSprite::RectangleSprite(std::string name) :
		sf::RectangleShape(),
		ISprite(name)
	{

	}
}
