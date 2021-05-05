#include <StraveEngine/Component/Transform.hpp>

#include <StraveEngine/Element/RectangleSprite.hpp>
#include <StraveEngine/Element/Texture.hpp>
#include <StraveEngine/Element/ITransformable.hpp>
#include <StraveEngine/Element/ISprite.hpp>
#include <StraveEngine/System/Convert.hpp>
#include <StraveEngine/Entity/GameObject.hpp>
#include <StraveEngine/Component/Mesh.hpp>


namespace Strave
{
	Transform::Transform(ISprite* sprite) :
		IComponent(),
		m_AssignedSprite(sprite),
		m_Position(Vector2f(0.0f, 0.0f)),
		m_Origin(Transform::GetDefaultOrigin()),
		m_Scale(Vector2f(1.0f, 1.0f)),
		m_Rotation(0.0f)
	{}

	Transform::Transform(Vector2f& position, Vector2f& scale, float rotation, std::string name) :
		IComponent(),
		m_AssignedSprite(UNDEF_PTR),
		m_Position(position),
		m_Origin(Vector2f(0.0f, 0.0f)),
		m_Scale(scale),
		m_Rotation(0.0f)
	{}

	Transform::Transform(ISprite* sprite, Vector2f& position, Vector2f& scale, float rotation, std::string name) :
		IComponent(name), 
		m_AssignedSprite(sprite),
		m_Position(position),
		m_Origin(Transform::GetDefaultOrigin()),
		m_Scale(scale),
		m_Rotation(rotation)
	{}

	Transform::Transform(const Transform& transform) :
		IComponent(transform),
		m_AssignedSprite(transform.m_AssignedSprite),
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

	void Transform::ApplyTransforms(void) const
	{
		if (m_AssignedSprite != UNDEF_PTR)
		{
			m_AssignedSprite->SetPosition(m_Position);
			m_AssignedSprite->SetScale(m_Scale);
			m_AssignedSprite->SetRotation(m_Rotation);

			m_AssignedSprite->SetOrigin(Vector2f(
				m_AssignedSprite->GetPosition().x + (m_AssignedSprite->GetTextureRect().width / 2),
				m_AssignedSprite->GetPosition().y + (m_AssignedSprite->GetTextureRect().height / 2)
			));
		}
	}

	void Transform::ApplyPosition(void) const
	{
		if (m_AssignedSprite != UNDEF_PTR)
			m_AssignedSprite->SetPosition(m_Position);
	}

	void Transform::ApplyOrigin(void) const
	{
		if (m_AssignedSprite != UNDEF_PTR)
			m_AssignedSprite->SetPosition(m_Origin);
	}

	void Transform::ApplyScale(void) const
	{
		if (m_AssignedSprite != UNDEF_PTR)
			m_AssignedSprite->SetScale(m_Scale);
	}

	void Transform::ApplyRotation(void) const
	{
		if (m_AssignedSprite != UNDEF_PTR)
			m_AssignedSprite->SetRotation(m_Rotation);
	}

	void Transform::ApplyDefaultOrigin() const
	{
		if (m_AssignedSprite != UNDEF_PTR)
		{
			m_AssignedSprite->SetOrigin(Vector2f(
				m_AssignedSprite->GetPosition().x + (m_AssignedSprite->GetTextureRect().width / 2),
				m_AssignedSprite->GetPosition().y + (m_AssignedSprite->GetTextureRect().height / 2)
			));
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

		if (m_AssignedSprite != UNDEF_PTR)
		{
			defaultOrigin = std::move(Vector2f(
				m_AssignedSprite->GetPosition().x + (m_AssignedSprite->GetTextureRect().width / 2),
				m_AssignedSprite->GetPosition().y + (m_AssignedSprite->GetTextureRect().height / 2)
			));
		}

		return defaultOrigin;
	}

	float Transform::GetDefaultRotation(void)
	{
		return UNDEF_FLOAT;
	}
}
