#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/Convert.hpp>
#include <StraveEngine/Element/ISprite.hpp>


namespace Strave
{
	class STRAVE_GRAPHICS_API RectangleSprite final : public sf::RectangleShape, public ISprite
	{
	public:
		RectangleSprite();
		RectangleSprite(std::string name);
		RectangleSprite(const RectangleSprite&) = default;
		~RectangleSprite() = default;

		inline ElementType GetElementType(void) const override final { return ElementType::RectangleSprite; }
		inline void* GetInstance(void) override final { return static_cast<RectangleSprite*>(this); }
		inline const sf::IntRect& GetTextureRect(void) const { return this->getTextureRect(); }

	protected:
		inline const Vector2f& GetPosition(void) const override final { return Convert::ToVector2(this->sf::RectangleShape::getPosition()); }
		inline const Vector2f& GetScale(void) const override final { return Convert::ToVector2(this->sf::RectangleShape::getScale()); }
		inline float GetRotation(void) const override final { return this->sf::RectangleShape::getRotation(); }
		inline void SetPosition(const Vector2f& position) override final { this->sf::RectangleShape::setPosition(Convert::ToVector2(position)); }
		inline void SetScale(const Vector2f& scale) override final { this->sf::RectangleShape::setScale(Convert::ToVector2(scale)); }
		inline void SetOrigin(const Vector2f& origin) override final { this->sf::RectangleShape::setOrigin(Convert::ToVector2(origin)); }
		inline void SetRotation(float rotation) override final { this->sf::RectangleShape::setRotation(rotation); }
	};
}

