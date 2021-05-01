#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/Entity/Object.hpp>


namespace Strave
{
	enum class STRAVE_ELEMENT_API ElementType
	{
		Texture = 0,
		Sprite,
		RectangleSprite,
		Circle,				// Not implmented yet
		Sqare,				// Not implmented yet
		Triangle			// Not implmented yet
	};

	class STRAVE_ELEMENT_API IElement abstract : public Object
	{
	public:
		virtual ~IElement() = default;

		virtual ElementType GetElementType(void) const = 0;

	protected:
		IElement() = default;
		IElement(std::string name);
		IElement(const IElement&) = default;
	};
}
