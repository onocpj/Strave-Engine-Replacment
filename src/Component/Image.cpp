#include <StraveEngine/Component/Image.hpp>

#include <StraveEngine/Component/Transform.hpp>
#include <StraveEngine/Element/Texture.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/Convert.hpp>


namespace Strave
{
	Image::Image(Transform* transforms) :
		IComponent(),
		m_Transforms(transforms),
		m_Sprite(new RectangleSprite()),
		m_Texture(UNDEF_PTR),
		m_NativeSize(Vector2f(0.0f, 0.0f))
	{
		SetNativeSize(m_NativeSize);
	}

	Image::Image(Transform* transforms, std::string name) :
		IComponent(name),
		m_Transforms(transforms),
		m_Sprite(new RectangleSprite()),
		m_Texture(UNDEF_PTR),
		m_NativeSize(Vector2f(0.0f, 0.0f))
	{
		SetNativeSize(m_NativeSize);
	}

	Image::Image(Transform* transforms, RectangleSprite& sprite, std::string name) :
		IComponent(name),
		m_Transforms(transforms),
		m_Sprite(&sprite),
		m_Texture(UNDEF_PTR),
		m_NativeSize(Vector2f(0.0f, 0.0f))
	{
		SetNativeSize(m_NativeSize);
	}

	Image::Image(Transform* transforms, Texture& texture, std::string name) :
		IComponent(name),
		m_Transforms(transforms),
		m_Sprite(new RectangleSprite()),
		m_Texture(&texture),
		m_NativeSize({ (float)m_Texture->getSize().x, (float)m_Texture->getSize().y })
	{
		this->ApplyTexture(texture);
		SetNativeSize(m_NativeSize);
	}

	Image::Image(Transform* transforms, RectangleSprite& sprite, Texture& texture, std::string name) :
		IComponent(name),
		m_Transforms(transforms),
		m_Sprite(&sprite),
		m_Texture(&texture),
		m_NativeSize({ (float)m_Texture->getSize().x, (float)m_Texture->getSize().y })
	{
		this->ApplyTexture(texture);
		SetNativeSize(m_NativeSize);
	}

	Image::Image(const Image& image) :
		IComponent(image),
		m_Transforms(new Transform(*image.m_Transforms)),
		m_Sprite(new RectangleSprite(*image.m_Sprite)),
		m_Texture(image.m_Texture),
		m_NativeSize(image.m_NativeSize)
	{
		this->ApplyTexture(*m_Texture);
		SetNativeSize(m_NativeSize);
	}

	void Image::SetNativeSize(Vector2f nativeSize)
	{
		m_NativeSize = nativeSize;
		m_Sprite->setSize(Convert::ToVector2(m_NativeSize));
	}

	void Image::UpdateTexture(const Texture& texture)
	{
		this->GetCorrectSprite().setTexture(&texture, true);
	}

	void Image::SelectImage(RectangleSprite& image)
	{
		m_Sprite = &image;
		this->ApplyTexture(*m_Texture);
	}

	void Image::ApplyTexture(Texture& texture)
	{
		m_Texture = &texture;

		if (m_Texture != UNDEF_PTR)
		{
			RectangleSprite* sprite = &Image::GetCorrectSprite();
			sprite->setTexture(m_Texture, true);

			// After texture was applied, apply default origin (center of the sprite)
			if (m_Transforms != UNDEF_PTR)
				m_Transforms->ApplyDefaultOrigin();
		}
	}

	void Image::RemoveTexture(void)
	{
		if (Object::Exists(m_Texture))
			m_Texture = UNDEF_PTR;
	}
}
