#pragma once

#include <StraveEngine/Element/ITransformable.hpp>
#include <StraveEngine/Element/IElement.hpp>
#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/Vector2.hpp>

namespace sf
{
	template<typename T> class Rect;

	typedef Rect<int> IntRect;
	typedef Rect<float> FloatRect;
}
namespace Strave
{
	class Transform;

	class STRAVE_ELEMENT_API ISprite abstract : public IElement, public ITransformable
	{
	private:
		friend Transform;

	public:
		ISprite();
		ISprite(std::string name);
		ISprite(const ISprite&) = default;
		virtual ~ISprite() = default;

		virtual void* GetInstance(void) = 0;
		virtual const sf::IntRect& GetTextureRect(void) const = 0;

	protected:
		virtual const Vector2f& GetPosition(void) const = 0;
		virtual const Vector2f& GetScale(void) const = 0;
		virtual float GetRotation(void) const = 0;
		virtual void SetPosition(const Vector2f& position) = 0;
		virtual void SetScale(const Vector2f& scale) = 0;
		virtual void SetOrigin(const Vector2f& origin) = 0;
		virtual void SetRotation(float rotation) = 0;
	};
}
