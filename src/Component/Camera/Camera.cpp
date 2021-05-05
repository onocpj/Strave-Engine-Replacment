#include <StraveEngine/Component/Camera/Camera.hpp>

#include <SFML/Graphics/View.hpp>

#include <StraveEngine/System/Convert.hpp>
#include <StraveEngine/System/Window.hpp>
#include <StraveEngine/System/ExceptionHandler.hpp>
#include <StraveEngine/Component/Camera/CameraContainer.hpp>
#include <StraveEngine/Entity/GameObject.hpp>


namespace Strave
{
	Camera::Camera() :
		IComponent(),
		m_KEY(CAM_KEY_UNASSIGNED),
		m_View(UNDEF_PTR),
		m_Transforms(UNDEF_PTR),
		m_ViewportSize(UNDEF_VECTOR2F),
		m_Enabled(true)
	{
		Camera::Init();
		ExceptionHandler::Handle(CameraContainer::Insert(*this, this->m_KEY));
	}

	Camera::Camera(std::string name) :
		IComponent(name),
		m_KEY(CAM_KEY_UNASSIGNED),
		m_View(UNDEF_PTR),
		m_Transforms(UNDEF_PTR),
		m_ViewportSize(UNDEF_VECTOR2F),
		m_Enabled(true)
	{
		Camera::Init();
		ExceptionHandler::Handle(CameraContainer::Insert(*this, this->m_KEY));
	}

	Camera::Camera(Transform* transforms, std::string name) :
		IComponent(name),
		m_KEY(CAM_KEY_UNASSIGNED),
		m_View(UNDEF_PTR),
		m_Transforms(UNDEF_PTR),
		m_ViewportSize(UNDEF_VECTOR2F),
		m_Enabled(true)
	{
		Camera::Init();
		ExceptionHandler::Handle(CameraContainer::Insert(*this, this->m_KEY));
	}

	Camera::Camera(const Camera& camera) :
		IComponent(camera),
		m_KEY(CAM_KEY_UNASSIGNED),
		m_View(camera.m_View),
		m_Transforms(new Transform(*camera.m_Transforms)),
		m_ViewportSize(camera.m_ViewportSize),
		m_Enabled(camera.m_Enabled)
	{
		Camera::Init();
		ExceptionHandler::Handle(CameraContainer::Insert(*this, this->m_KEY));
	}

	void Camera::Init(void)
	{
		if (m_Transforms == UNDEF_PTR)
		{
			Vector2f position = { 0.0f, 0.0f };
			Vector2f size = { 0.0f, 0.0f };
			float rotation = 0.0f;

			m_Transforms = new Transform(position, size, rotation);
		}

		sf::Vector2f initPosition = Convert::ToVector2(m_Transforms->GetPosition());	
		sf::Vector2f initViewportSize = sf::Vector2f((float)Window::GetResolution().GetWidth(), (float)Window::GetResolution().GetHeight());

		m_ViewportSize = Convert::ToVector2(initViewportSize);

		m_View = new sf::View(initPosition, initViewportSize);
	}

	void Camera::SetPosition(Vector2f position)
	{
		m_Transforms->SetPosition(position);
		m_View->setCenter(Convert::ToVector2(m_Transforms->GetPosition()));
	}

	void Camera::SetRotation(float rotation)
	{
		m_Transforms->SetRotation(rotation);
		m_View->setRotation(m_Transforms->GetRotation());
	}

	void Camera::SetViewportSize(Vector2f size)
	{
		m_ViewportSize = size;
		m_View->setSize(Convert::ToVector2(m_ViewportSize));
	}

	Camera& Camera::GetCamera(Uint64 camera)
	{
		return *CameraContainer::s_CameraContainer->GetElement(camera);
	}

	void Camera::Delete(void) const
	{
		ExceptionHandler::Handle(CameraContainer::Erase(this->m_KEY));
		delete this;
	}

	void Camera::Delete(Uint64 camera)
	{
		Camera* instance = CameraContainer::s_CameraContainer->GetElement(camera);
		ExceptionHandler::Handle(CameraContainer::Erase(instance->m_KEY));
		delete instance;
	}

	void Camera::AssignTo(GameObject& object)
	{
		if (!object.HaveAssignComponent<Camera>())
			object.AssignComponent<Camera>(*this);
	}

	void Camera::Switch(GameObject& fromObject, GameObject& toObject)
	{
		if (!toObject.HaveAssignComponent<Camera>())
		{
			fromObject.UnassignComponent<Camera>();
			toObject.AssignComponent<Camera>(*this);
		}
	}

	void Camera::AssignTo(Camera& camera, GameObject& object)
	{
		if (!object.HaveAssignComponent<Camera>())
			object.AssignComponent<Camera>(camera);
	}

	void Camera::Switch(Camera& camera, GameObject& fromObject, GameObject& toObject)
	{
		if (!toObject.HaveAssignComponent<Camera>())
		{
			fromObject.UnassignComponent<Camera>();
			toObject.AssignComponent<Camera>(camera);
		}
	}

	void Camera::Update(void)
	{
		if (m_Enabled)
		{
			sf::Vector2f position = Convert::ToVector2(m_Transforms->GetPosition());
			float rotation = m_Transforms->GetRotation();

			m_View->setCenter(Convert::ToVector2(m_Transforms->GetPosition()));
			m_View->setRotation(m_Transforms->GetRotation());
		}
	}
}
