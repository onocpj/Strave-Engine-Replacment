#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/Element/ISprite.hpp>


namespace Strave
{
	class STRAVE_GRAPHICS_API Sprite final : public sf::Sprite, public ISprite
	{
	public:
		Sprite();
		Sprite(std::string name);
		~Sprite() = default;
		Sprite(const Sprite&) = default;

		inline void* GetInstance(void) override final { return static_cast<Sprite*>(this); }
		inline ElementType GetElementType(void) const override final { return ElementType::Sprite; }
	};
}
