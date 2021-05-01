#pragma once

#include <SFML/Graphics/Transformable.hpp>

#include <StraveEngine/System/Export.hpp>


namespace Strave
{
	class STRAVE_ELEMENT_API ITransformable abstract : public sf::Transformable
	{
	public:
		ITransformable() = default;
		ITransformable(const ITransformable& transformable) = default;
		virtual ~ITransformable() = default;
	};
}
