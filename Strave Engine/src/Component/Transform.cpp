#include <StraveEngine/Component/Transform.hpp>

#include <StraveEngine/Element/ISprite.hpp>
#include <StraveEngine/Element/Sprite.hpp>
#include <StraveEngine/Element/RectangleSprite.hpp>
#include <StraveEngine/System/Convert.hpp>
#include <StraveEngine/Entity/GameObject.hpp>
#include <StraveEngine/Component/Mesh.hpp>


namespace Strave
{
	Transform::Transform(GameObject* object) :
		IComponent(),
		m_GameObject(object),
		m_Position(Vector2f(0.0f, 0.0f)),
		m_Origin(Transform::GetDefaultOrigin()),
		m_Scale(Vector2f(1.0f, 1.0f)),
		m_Rotation(0.0f)
	{}

	Transform::Transform(GameObject* object, Vector2f& position, Vector2f& scale, float rotation, std::string name) :
		IComponent(name), 
		m_GameObject(object),
		m_Position(position),
		m_Origin(Transform::GetDefaultOrigin()),
		m_Scale(scale),
		m_Rotation(rotation)
	{}

	Transform::Transform(const Transform& transform) :
		IComponent(transform)
	{
		m_GameObject = transform.m_GameObject;
		m_Position = transform.m_Position;
		m_Origin = transform.m_Origin;
		m_Rotation = transform.m_Rotation;
		m_Scale = transform.m_Scale;
	}

	void Transform::SetPosition(Vector2f& position) 
	{ 
		m_Position = position; 
		Transform::ApplyPosition();
	}

	void Transform::SetOrigin(Vector2f& origin)
	{
		m_Origin = origin;
		Transform::ApplyOrigin();
	}

	void Transform::SetScale(Vector2f& scale) 
	{ 
		m_Scale = scale;
		Transform::ApplyScale();
	}

	void Transform::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		Transform::ApplyRotation();
	}

	void Transform::ApplyTransforms(void) const
	{
		Mesh* mesh = &m_GameObject->GetComponent<Mesh>();
		if (mesh != UNDEF_PTR)
		{
			Sprite* sprite = UNDEF_PTR;
			RectangleSprite* rectSprite = UNDEF_PTR;

			MeshType meshType = mesh->GetMeshType();

			if (meshType == MeshType::Sprite)
			{
				sprite = &mesh->GetSprite<Sprite>();
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
				rectSprite = &mesh->GetSprite<RectangleSprite>();
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
		Mesh* mesh = &m_GameObject->GetComponent<Mesh>();
		if (mesh != UNDEF_PTR)
		{
			Sprite* sprite = UNDEF_PTR;
			RectangleSprite* rectSprite = UNDEF_PTR;

			MeshType meshType = mesh->GetMeshType();

			if (meshType == MeshType::Sprite)
			{
				sprite = &mesh->GetSprite<Sprite>();
				sprite->setPosition(Convert::ToVector2(m_Position));
			}
			else
			{
				rectSprite = &mesh->GetSprite<RectangleSprite>();
				rectSprite->setPosition(Convert::ToVector2(m_Position));
			}
		}
	}

	void Transform::ApplyOrigin(void) const
	{
		Mesh* mesh = &m_GameObject->GetComponent<Mesh>();
		if (m_GameObject != UNDEF_PTR)
		{
			Sprite* sprite = UNDEF_PTR;
			RectangleSprite* rectSprite = UNDEF_PTR;

			MeshType meshType = mesh->GetMeshType();

			if (meshType == MeshType::Sprite)
			{
				sprite = &mesh->GetSprite<Sprite>();
				sprite->setPosition(Convert::ToVector2(m_Origin));
			}
			else
			{
				rectSprite = &mesh->GetSprite<RectangleSprite>();
				rectSprite->setPosition(Convert::ToVector2(m_Origin));
			}
		}
	}

	void Transform::ApplyScale(void) const
	{
		Mesh* mesh = &m_GameObject->GetComponent<Mesh>();
		if (mesh != UNDEF_PTR)
		{
			Sprite* sprite = UNDEF_PTR;
			RectangleSprite* rectSprite = UNDEF_PTR;

			MeshType meshType = mesh->GetMeshType();

			if (meshType == MeshType::Sprite)
			{
				sprite = &mesh->GetSprite<Sprite>();
				sprite->setScale(Convert::ToVector2(m_Scale));
			}
			else
			{
				rectSprite = &mesh->GetSprite<RectangleSprite>();
				rectSprite->setScale(Convert::ToVector2(m_Scale));
			}
		}
	}

	void Transform::ApplyRotation(void) const
	{
		Mesh* mesh = &m_GameObject->GetComponent<Mesh>();
		if (mesh != UNDEF_PTR)
		{
			Sprite* sprite = UNDEF_PTR;
			RectangleSprite* rectSprite = UNDEF_PTR;

			MeshType meshType = mesh->GetMeshType();

			if (meshType == MeshType::Sprite)
			{
				sprite = &mesh->GetSprite<Sprite>();
				sprite->setRotation(m_Rotation);
			}
			else
			{
				rectSprite = &mesh->GetSprite<RectangleSprite>();
				rectSprite->setRotation(m_Rotation);
			}
		}
	}

	void Transform::ApplyDefaultOrigin() const
	{
		Mesh* mesh = &m_GameObject->GetComponent<Mesh>();
		if (mesh != UNDEF_PTR)
		{
			Sprite* sprite = UNDEF_PTR;
			RectangleSprite* rectSprite = UNDEF_PTR;

			MeshType meshType = mesh->GetMeshType();

			if (meshType == MeshType::Sprite)
			{
				sprite = &mesh->GetSprite<Sprite>();
				sprite->setOrigin(Convert::ToVector2(Vector2f(
					sprite->getPosition().x + (sprite->getTextureRect().width / 2),
					sprite->getPosition().y + (sprite->getTextureRect().height / 2)
				)));
			}
			else
			{
				rectSprite = &mesh->GetSprite<RectangleSprite>();
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
		Mesh* mesh = &m_GameObject->GetComponent<Mesh>();

		if (mesh != UNDEF_PTR)
		{
			Sprite* sprite = UNDEF_PTR;
			RectangleSprite* rectSprite = UNDEF_PTR;

			MeshType meshType = mesh->GetMeshType();

			if (meshType == MeshType::Sprite)
			{
				sprite = &mesh->GetSprite<Sprite>();
				defaultOrigin = std::move(Vector2f(
					sprite->getPosition().x + (sprite->getTextureRect().width / 2),
					sprite->getPosition().y + (sprite->getTextureRect().height / 2)
				));

				return defaultOrigin;
			}
			else
			{
				rectSprite = &mesh->GetSprite<RectangleSprite>();
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
