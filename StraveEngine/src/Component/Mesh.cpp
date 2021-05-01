#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <StraveEngine/Component/Mesh.hpp>

#include <StraveEngine/Element/Sprite.hpp>
#include <StraveEngine/Element/IElement.hpp>
#include <StraveEngine/Element/RectangleSprite.hpp>
#include <StraveEngine/Element/Texture.hpp>
#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/Component/Transform.hpp>


namespace Strave
{
	Mesh::Mesh(Transform* transforms) :
		IComponent(),
		m_Transforms(transforms),
		m_Sprite(new Sprite()),
		m_Texture(UNDEF_PTR)
	{}

	Mesh::Mesh(Transform* transforms, std::string name) :
		IComponent(name),
		m_Transforms(transforms),
		m_Sprite(new Sprite()),
		m_Texture(UNDEF_PTR)
	{}

	Mesh::Mesh(Transform* transforms, Sprite& sprite, std::string name) :
		IComponent(name),
		m_Transforms(transforms),
		m_Sprite(&sprite),
		m_Texture(UNDEF_PTR)
	{}

	Mesh::Mesh(Transform* transforms, Texture& texture, std::string name) :
		IComponent(name),
		m_Transforms(transforms),
		m_Sprite(new Sprite()),
		m_Texture(&texture)
	{
		this->ApplyTexture(texture);
	}

	Mesh::Mesh(Transform* transforms, Sprite& sprite, Texture& texture, std::string name) :
		IComponent(name),
		m_Transforms(transforms),
		m_Sprite(&sprite),
		m_Texture(&texture)
	{
		this->ApplyTexture(texture);
	}

	Mesh::Mesh(const Mesh& mesh) :
		IComponent(mesh),
		m_Transforms(mesh.m_Transforms),
		m_Sprite(mesh.m_Sprite),
		m_Texture(mesh.m_Texture)
	{
		this->ApplyTexture(*m_Texture);
	}

	void Mesh::UpdateTexture(const Texture& texture)
	{
		this->GetCorrectSprite().setTexture(texture, true);
	}

	void Mesh::SelectMesh(Sprite& sprite)
	{
		m_Sprite = &sprite;
		this->ApplyTexture(*m_Texture);
	}

	void Mesh::ApplyTexture(Texture& texture)
	{
		m_Texture = &texture;

		if (m_Texture != UNDEF_PTR)
		{
			Sprite* sprite = &Mesh::GetCorrectSprite();
			sprite->setTexture(*m_Texture, true);

			// After texture was applied, apply default origin (center of the sprite)
			if (m_Transforms != UNDEF_PTR)
				m_Transforms->ApplyDefaultOrigin();
		}
	}

	void Mesh::RemoveTexture(void)
	{
		if (Object::Exists(m_Texture))
			m_Texture = UNDEF_PTR;
	}
}
