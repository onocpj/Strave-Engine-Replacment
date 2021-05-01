#include <StraveEngine/Element/ISprite.hpp>


namespace Strave
{
	ISprite::ISprite() :
		IElement(),
		ITransformable()
	{}

	ISprite::ISprite(std::string name) :
		IElement(name),
		ITransformable()
	{}
}
