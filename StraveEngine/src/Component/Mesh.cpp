#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <StraveEngine/Component/Mesh.hpp>

#include <StraveEngine/Element/IElement.hpp>
#include <StraveEngine/Element/Sprite.hpp>
#include <StraveEngine/Element/RectangleSprite.hpp>
#include <StraveEngine/Element/Texture.hpp>
#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/Component/Transform.hpp>


namespace Strave
{
	MeshType TransformMeshType(const ISprite& element);
	state_t TextureAssigned(const Texture* texture);

	Mesh::Mesh(MeshType meshType, Transform* transforms) :
		IComponent(),
		m_Transforms(transforms),
		m_Type(meshType),
		m_Sprite(new Sprite()),
		m_Texture(UNDEF_PTR)
	{}

	Mesh::Mesh(MeshType meshType, Transform* transforms, std::string name) :
		IComponent(name),
		m_Transforms(transforms),
		m_Type(meshType),
		m_Sprite(new Sprite()),
		m_Texture(UNDEF_PTR)
	{}

	Mesh::Mesh(Transform* transforms, ISprite& sprite, std::string name) :
		IComponent(name),
		m_Transforms(transforms),
		m_Type(TransformMeshType(sprite)),
		m_Sprite(&sprite),
		m_Texture(UNDEF_PTR)
	{}

	Mesh::Mesh(MeshType meshType, Transform* transforms, Texture& texture, std::string name) :
		IComponent(name),
		m_Transforms(transforms),
		m_Type(meshType),
		m_Sprite(new Sprite()),
		m_Texture(&texture)
	{
		this->ApplyTexture(texture);
	}

	Mesh::Mesh(Transform* transforms, ISprite& sprite, Texture& texture, std::string name) :
		IComponent(name),
		m_Transforms(transforms),
		m_Type(TransformMeshType(sprite)),
		m_Sprite(&sprite),
		m_Texture(&texture)
	{
		this->ApplyTexture(texture);
	}

	Mesh::Mesh(const Mesh& mesh) :
		IComponent(mesh),
		m_Transforms(mesh.m_Transforms),
		m_Type(mesh.m_Type),
		m_Sprite(mesh.m_Sprite),
		m_Texture(mesh.m_Texture)
	{}

	void Mesh::UpdateTexture(const Texture& texture)
	{
		switch (m_Type)
		{
			case MeshType::Sprite: this->GetSprite<Sprite>().setTexture(texture, true); break;
			case MeshType::RectangleSprite: this->GetSprite<RectangleSprite>().setTexture(&texture, true); break;
			default: break;
		}
	}

	void Mesh::SelectMesh(ISprite& sprite)
	{
		m_Type = TransformMeshType(sprite);
		m_Sprite = &sprite;

		this->ApplyTexture(*m_Texture);
	}

	void Mesh::ApplyTexture(Texture& texture)
	{
		m_Texture = &texture;

		if (m_Texture != UNDEF_PTR)
		{
			if (m_Type == MeshType::Sprite)
			{
				Sprite* sprite = &Mesh::GetSprite<Sprite>();
				sprite->setTexture(*m_Texture, true);
			}
			else
			{
				RectangleSprite* rectSprite = &Mesh::GetSprite<RectangleSprite>();
				rectSprite->setTexture(m_Texture, true);
			}

			// After texture was applied, apply default origin (center of the sprite)
			if (m_Transforms != UNDEF_PTR)
				m_Transforms->ApplyDefaultOrigin();
		}
	}

	void Mesh::RemoveTexture(void)
	{
		if (TextureAssigned(m_Texture))
			m_Texture = UNDEF_PTR;
	}

	MeshType TransformMeshType(const ISprite& element)
	{
		return static_cast<MeshType>(element.GetElementType());
	}

	state_t TextureAssigned(const Texture* texture)
	{
		return texture != nullptr ? true : false;
	}
}
