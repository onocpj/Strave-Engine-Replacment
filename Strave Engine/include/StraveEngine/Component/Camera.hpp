#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/Component/IComponent.hpp>

#include <string>


namespace
{
	class View;
}
namespace Strave 
{
	class GameObject;
	class Transforms;

	class STRAVE_ENTITY_API Camera final : public IComponent
	{
	public:
		Camera() = default;
		Camera(std::string name);
		Camera(GameObject* object, std::string name = EMPTY_STR);
		~Camera() = default;
		Camera(const Camera&) = default;

		inline const Vector2f& GetPosiiton(void) const { return m_CameraPosition; }

	protected:
		void UpdateViewport(const WindowsWindow& window);

	private:
		std::shared_ptr<CAMERA_VIEW>	m_Camera2D;
		Vector2f						m_CameraPosition;
		Vector2f						m_ViewportSize;
		GameObject2D* m_AssignedGameObject2D;

	};
}
