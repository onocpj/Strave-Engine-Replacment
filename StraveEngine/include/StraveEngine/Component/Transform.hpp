#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/Component/IComponent.hpp>
#include <StraveEngine/System/Vector2.hpp>


namespace Strave
{	
	class Mesh;

	class STRAVE_COMPONENT_API Transform final : public IComponent
	{
	public:
		Transform(Mesh* mesh);
		Transform(Vector2f& position, Vector2f& scale, float rotation, std::string name = EMPTY_STR);
		Transform(Mesh* mesh, Vector2f& position, Vector2f& scale, float rotation, std::string name = EMPTY_STR);
		~Transform() = default;
		Transform(const Transform&);

		void SetPosition(Vector2f position);
		void SetOrigin(Vector2f origin);
		void SetScale(Vector2f scale);
		void SetRotation(float rotation);
		inline ComponentType GetComponentType(void) const override final { return ComponentType::Transform; }
		inline const Vector2f& GetPosition(void) const { return m_Position; }
		inline const Vector2f& GetOrigin(void) const { return m_Origin; };
		inline const Vector2f& GetScale(void) const { return m_Scale; }
		inline float GetRotation(void) const { return m_Rotation; }
		Vector2f GetDefaultPosition(void);
		Vector2f GetDefaultScale(void);
		Vector2f GetDefaultOrigin(void);
		float GetDefaultRotation(void);
		void ApplyTransforms(void) const;
		void ApplyPosition(void) const;
		void ApplyOrigin(void) const;
		void ApplyScale(void) const;
		void ApplyRotation(void) const;
		void ApplyDefaultOrigin() const;

	private:
		Mesh*		m_Mesh;
		Vector2f	m_Position;
		Vector2f	m_Scale;
		Vector2f	m_Origin;
		float		m_Rotation;
	};
}
