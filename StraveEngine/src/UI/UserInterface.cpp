#include <StraveEngine/UI/UserInterface.hpp>

#include <StraveEngine/System/ExceptionHandler.hpp>
#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/Component/Transform.hpp>
#include <StraveEngine/Component/Mesh.hpp>
#include <StraveEngine/UI/UserInterfaceContainer.hpp>


namespace Strave
{
	UserInterface::UserInterface() :
		Object(),
		m_Transform(new Transform(this->m_Mesh)),
		m_Mesh(new Mesh(MeshType::RectangleSprite, this->m_Transform)),
		m_ShowState(true)
	{
		ExceptionHandler::Handle(UserInterfaceContainer::Insert(*this, this->m_KEY));
	}

	UserInterface::UserInterface(std::string name) :
		Object(name),
		m_Transform(new Transform(this->m_Mesh)),
		m_Mesh(new Mesh(MeshType::RectangleSprite, this->m_Transform)),
		m_ShowState(true)
	{
		ExceptionHandler::Handle(UserInterfaceContainer::Insert(*this, this->m_KEY));
	}

	UserInterface::UserInterface(UserInterface& ui) :
		Object(),
		m_Transform(ui.m_Transform),
		m_Mesh(new Mesh(MeshType::RectangleSprite, this->m_Transform)),
		m_ShowState(ui.m_ShowState)
	{
		ExceptionHandler::Handle(UserInterfaceContainer::Insert(*this, this->m_KEY));
	}
}
