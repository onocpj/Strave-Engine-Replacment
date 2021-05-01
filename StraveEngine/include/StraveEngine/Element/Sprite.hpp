#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/Convert.hpp>
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

		inline ElementType GetElementType(void) const override final { return ElementType::Sprite; }
		inline void* GetInstance(void) override final { return static_cast<Sprite*>(this); }
		inline const sf::IntRect& GetTextureRect(void) const { return this->getTextureRect(); }

	protected:
		inline const Vector2f& GetPosition(void) const override final { return Convert::ToVector2(this->sf::Sprite::getPosition()); }
		inline const Vector2f& GetScale(void) const override final { return Convert::ToVector2(this->sf::Sprite::getScale()); }
		inline float GetRotation(void) const override final { return this->sf::Sprite::getRotation(); }
		inline void SetPosition(const Vector2f& position) override final { this->sf::Sprite::setPosition(Convert::ToVector2(position)); }
		inline void SetScale(const Vector2f& scale) override final { this->sf::Sprite::setScale(Convert::ToVector2(scale)); }
		inline void SetOrigin(const Vector2f& origin) override final { this->sf::Sprite::setOrigin(Convert::ToVector2(origin)); }
		inline void SetRotation(float rotation) override final { this->sf::Sprite::setRotation(rotation); }
	};
}
