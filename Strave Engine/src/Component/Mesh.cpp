#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <StraveEngine/Component/Mesh.hpp>
#include <StraveEngine/Element/IElement.hpp>
#include <StraveEngine/Element/Sprite.hpp>
#include <StraveEngine/Element/RectangleSprite.hpp>
#include <StraveEngine/Element/Texture.hpp>
#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/Entity/GameObject.hpp>
#include <StraveEngine/Component/Transform.hpp>


namespace Strave
{
	MeshType TransformMeshType(const ISprite& element);
	state_t TextureAssigned(const Texture* texture);

	Mesh::Mesh(GameObject* object) :
		IComponent(),
		m_GameObject(object),
		m_Type(MeshType::Sprite),
		m_Sprite(new Sprite()),
		m_Texture(UNDEF_PTR)
	{}

	Mesh::Mesh(GameObject* object, std::string name) :
		IComponent(name),
		m_GameObject(object),
		m_Type(MeshType::Sprite),
		m_Sprite(new Sprite()),
		m_Texture(UNDEF_PTR)
	{}

	Mesh::Mesh(GameObject* object, ISprite& sprite, std::string name) :
		IComponent(name),
		m_GameObject(object),
		m_Type(TransformMeshType(sprite)),
		m_Sprite(&sprite),
		m_Texture(UNDEF_PTR)
	{}

	Mesh::Mesh(GameObject* object, Texture& texture, std::string name) :
		IComponent(name),
		m_GameObject(object),
		m_Type(MeshType::Sprite),
		m_Sprite(new Sprite()),
		m_Texture(&texture)
	{
		this->ApplyTexture(texture);
	}

	Mesh::Mesh(GameObject* object, ISprite& sprite, Texture& texture, std::string name) :
		IComponent(name),
		m_GameObject(object),
		m_Type(TransformMeshType(sprite)),
		m_Sprite(&sprite),
		m_Texture(&texture)
	{
		this->ApplyTexture(texture);
	}

	Mesh::Mesh(const Mesh& mesh) :
		IComponent(mesh)
	{
		m_GameObject = mesh.m_GameObject;
		m_Type = mesh.m_Type;
		m_Sprite = mesh.m_Sprite;
		m_Texture = mesh.m_Texture;
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
		Transform* transforms = &m_GameObject->GetComponent<Transform>();

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
			if (transforms != UNDEF_PTR)
				transforms->ApplyDefaultOrigin();
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
