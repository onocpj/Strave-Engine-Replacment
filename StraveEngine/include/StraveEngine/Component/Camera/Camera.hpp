#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/Vector2.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/Component/IComponent.hpp>
#include <StraveEngine/Component/Transform.hpp>

#include <string>


#define CAM_KEY_UNASSIGNED	ERROR_TYPE
#define CAM_MAIN_CAMERA		0


namespace sf
{
	class View;
}
namespace Strave 
{
	class Window;
	class Transform;
	class GameObject;
	class Renderer;

	class STRAVE_ENTITY_API Camera final : public IComponent
	{
	private:
		friend Renderer;

	public:
		Camera();
		Camera(std::string name);
		Camera(Transform* transforms, std::string name = EMPTY_STR);
		Camera(const Camera&);

		inline virtual ComponentType GetComponentType(void) const override final { return ComponentType::Camera; }

		void SetPosition(Vector2f position);
		void SetRotation(float rotation);
		void SetViewportSize(Vector2f size);
		inline const Uint64& GetKey(void) const { return m_KEY; }
		inline const Vector2f& GetPosition(void) const { return m_Transforms->GetPosition(); }
		inline const float GetRotation(void) const { return m_Transforms->GetRotation(); }
		inline const Vector2f& GetViewportSize(void) const { return m_ViewportSize; }
		static Camera& GetCamera(Uint64 camera);
		void Delete(void) const;
		static void Delete(Uint64 camera);
		inline void Enable(void) { m_Enabled = true; }
		inline void Disable(void) { m_Enabled = false; }
		inline void AssignTransforms(Transform& transforms) { m_Transforms = &transforms; }
		void AssignTo(GameObject& object);
		static void AssignTo(Camera& camera, GameObject& object);
		void Switch(GameObject& fromObject, GameObject& toObject);
		static void Switch(Camera& camera, GameObject& fromObject, GameObject& toObject);

	private:
		~Camera() = default;
		void Init(void);
		
	protected:
		inline const sf::View& GetCameraView(void) const { return *m_View; }
		void Update(void);

	private:
		Uint64		m_KEY;
		sf::View*	m_View;
		Transform*	m_Transforms;
		Vector2f	m_ViewportSize;
		bool		m_Enabled;
	};
}
