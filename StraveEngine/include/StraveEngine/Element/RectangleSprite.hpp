#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/Element/ISprite.hpp>


namespace Strave
{
	class STRAVE_GRAPHICS_API RectangleSprite final : public sf::RectangleShape, public ISprite
	{
	public:
		RectangleSprite();
		RectangleSprite(std::string name);
		~RectangleSprite() = default;
		RectangleSprite(const RectangleSprite&) = default;

		inline void* GetInstance(void) override final { return static_cast<RectangleSprite*>(this); }
		inline ElementType GetElementType(void) const override final { return ElementType::RectangleSprite; }
	};
}

