#include <StraveEngine/Component/Transform.hpp>

#include <StraveEngine/Element/ISprite.hpp>
#include <StraveEngine/Element/Sprite.hpp>
#include <StraveEngine/Element/RectangleSprite.hpp>
#include <StraveEngine/Element/Texture.hpp>
#include <StraveEngine/System/Convert.hpp>
#include <StraveEngine/Entity/GameObject.hpp>
#include <StraveEngine/Component/Mesh.hpp>


namespace Strave
{
	Transform::Transform(Mesh* mesh) :
		IComponent(),
		m_Mesh(mesh),
		m_Position(Vector2f(0.0f, 0.0f)),
		m_Origin(Transform::GetDefaultOrigin()),
		m_Scale(Vector2f(1.0f, 1.0f)),
		m_Rotation(0.0f)
	{}

	Transform::Transform(Vector2f& position, Vector2f& scale, float rotation, std::string name) :
		IComponent(),
		m_Mesh(UNDEF_PTR),
		m_Position(position),
		m_Origin(Vector2f(0.0f, 0.0f)),
		m_Scale(scale),
		m_Rotation(0.0f)
	{

	}

	Transform::Transform(Mesh* mesh, Vector2f& position, Vector2f& scale, float rotation, std::string name) :
		IComponent(name), 
		m_Mesh(mesh),
		m_Position(position),
		m_Origin(Transform::GetDefaultOrigin()),
		m_Scale(scale),
		m_Rotation(rotation)
	{}

	Transform::Transform(const Transform& transform) :
		IComponent(transform),
		m_Mesh(transform.m_Mesh),
		m_Position(transform.m_Position),
		m_Origin(transform.m_Origin),
		m_Rotation(transform.m_Rotation),
		m_Scale(transform.m_Scale)
	{}

	void Transform::SetPosition(Vector2f position) 
	{ 
		m_Position = std::move(position); 
		Transform::ApplyPosition();
	}

	void Transform::SetOrigin(Vector2f origin)
	{
		m_Origin = std::move(origin);
		Transform::ApplyOrigin();
	}

	void Transform::SetScale(Vector2f scale) 
	{ 
		m_Scale = std::move(scale);
		Transform::ApplyScale();
	}

	void Transform::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		Transform::ApplyRotation();
	}

	const Vector2f Transform::GetSize(void) const
	{
		Texture& texture = m_Mesh->GetTexture();

		return Vector2f(
			texture.getSize().x * m_Scale.x,
			texture.getSize().y * m_Scale.y
		);
	}

	void Transform::ApplyTransforms(void) const
	{
		if (m_Mesh != UNDEF_PTR)
		{
			Sprite* sprite = UNDEF_PTR;
			RectangleSprite* rectSprite = UNDEF_PTR;

			MeshType meshType = m_Mesh->GetMeshType();

			if (meshType == MeshType::Sprite)
			{
				sprite = &m_Mesh->GetSprite<Sprite>();
				sprite->setPosition(Convert::ToVector2(m_Position));
				sprite->setScale(Convert::ToVector2(m_Scale));
				sprite->setRotation(m_Rotation);

				sprite->setOrigin(Convert::ToVector2(Vector2f(
					sprite->getPosition().x + (sprite->getTextureRect().width / 2),
					sprite->getPosition().y + (sprite->getTextureRect().height / 2)
				)));
			}
			else
			{
				rectSprite = &m_Mesh->GetSprite<RectangleSprite>();
				rectSprite->setPosition(Convert::ToVector2(m_Position));
				rectSprite->setScale(Convert::ToVector2(m_Scale));
				rectSprite->setRotation(m_Rotation);

				rectSprite->setOrigin(Convert::ToVector2(Vector2f(
					rectSprite->getPosition().x + (rectSprite->getTextureRect().width / 2),
					rectSprite->getPosition().y + (rectSprite->getTextureRect().height / 2)
				)));
			}
		}
	}

	void Transform::ApplyPosition(void) const
	{
		if (m_Mesh != UNDEF_PTR)
		{
			Sprite* sprite = UNDEF_PTR;
			RectangleSprite* rectSprite = UNDEF_PTR;

			MeshType meshType = m_Mesh->GetMeshType();

			if (meshType == MeshType::Sprite)
			{
				sprite = &m_Mesh->GetSprite<Sprite>();
				sprite->setPosition(Convert::ToVector2(m_Position));
			}
			else
			{
				rectSprite = &m_Mesh->GetSprite<RectangleSprite>();
				rectSprite->setPosition(Convert::ToVector2(m_Position));
			}
		}
	}

	void Transform::ApplyOrigin(void) const
	{
		if (m_Mesh != UNDEF_PTR)
		{
			Sprite* sprite = UNDEF_PTR;
			RectangleSprite* rectSprite = UNDEF_PTR;

			MeshType meshType = m_Mesh->GetMeshType();

			if (meshType == MeshType::Sprite)
			{
				sprite = &m_Mesh->GetSprite<Sprite>();
				sprite->setPosition(Convert::ToVector2(m_Origin));
			}
			else
			{
				rectSprite = &m_Mesh->GetSprite<RectangleSprite>();
				rectSprite->setPosition(Convert::ToVector2(m_Origin));
			}
		}
	}

	void Transform::ApplyScale(void) const
	{
		if (m_Mesh != UNDEF_PTR)
		{
			Sprite* sprite = UNDEF_PTR;
			RectangleSprite* rectSprite = UNDEF_PTR;

			MeshType meshType = m_Mesh->GetMeshType();

			if (meshType == MeshType::Sprite)
			{
				sprite = &m_Mesh->GetSprite<Sprite>();
				sprite->setScale(Convert::ToVector2(m_Scale));
			}
			else
			{
				rectSprite = &m_Mesh->GetSprite<RectangleSprite>();
				rectSprite->setScale(Convert::ToVector2(m_Scale));
			}
		}
	}

	void Transform::ApplyRotation(void) const
	{
		if (m_Mesh != UNDEF_PTR)
		{
			Sprite* sprite = UNDEF_PTR;
			RectangleSprite* rectSprite = UNDEF_PTR;

			MeshType meshType = m_Mesh->GetMeshType();

			if (meshType == MeshType::Sprite)
			{
				sprite = &m_Mesh->GetSprite<Sprite>();
				sprite->setRotation(m_Rotation);
			}
			else
			{
				rectSprite = &m_Mesh->GetSprite<RectangleSprite>();
				rectSprite->setRotation(m_Rotation);
			}
		}
	}

	void Transform::ApplyDefaultOrigin() const
	{
		if (m_Mesh != UNDEF_PTR)
		{
			Sprite* sprite = UNDEF_PTR;
			RectangleSprite* rectSprite = UNDEF_PTR;

			MeshType meshType = m_Mesh->GetMeshType();

			if (meshType == MeshType::Sprite)
			{
				sprite = &m_Mesh->GetSprite<Sprite>();
				sprite->setOrigin(Convert::ToVector2(Vector2f(
					sprite->getPosition().x + (sprite->getTextureRect().width / 2),
					sprite->getPosition().y + (sprite->getTextureRect().height / 2)
				)));
			}
			else
			{
				rectSprite = &m_Mesh->GetSprite<RectangleSprite>();
				rectSprite->setOrigin(Convert::ToVector2(Vector2f(
					rectSprite->getPosition().x + (rectSprite->getTextureRect().width / 2),
					rectSprite->getPosition().y + (rectSprite->getTextureRect().height / 2)
				)));
			}
		}
	}

	Vector2f Transform::GetDefaultPosition(void)
	{
		return UNDEF_VECTOR2F;
	}

	Vector2f Transform::GetDefaultScale(void)
	{
		return UNDEF_VECTOR2F;
	}

	Vector2f Transform::GetDefaultOrigin(void)
	{
		Vector2f defaultOrigin = UNDEF_VECTOR2F;

		if (m_Mesh != UNDEF_PTR)
		{
			Sprite* sprite = UNDEF_PTR;
			RectangleSprite* rectSprite = UNDEF_PTR;

			MeshType meshType = m_Mesh->GetMeshType();

			if (meshType == MeshType::Sprite)
			{
				sprite = &m_Mesh->GetSprite<Sprite>();
				defaultOrigin = std::move(Vector2f(
					sprite->getPosition().x + (sprite->getTextureRect().width / 2),
					sprite->getPosition().y + (sprite->getTextureRect().height / 2)
				));

				return defaultOrigin;
			}
			else
			{
				rectSprite = &m_Mesh->GetSprite<RectangleSprite>();
				defaultOrigin = std::move(Vector2f(
					rectSprite->getPosition().x + (rectSprite->getTextureRect().width / 2),
					rectSprite->getPosition().y + (rectSprite->getTextureRect().height / 2)
				));

				return defaultOrigin;
			}
		}

		return defaultOrigin;
	}

	float Transform::GetDefaultRotation(void)
	{
		return UNDEF_FLOAT;
	}
}
