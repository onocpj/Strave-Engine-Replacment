#include <StraveEngine/UI/UserInterface.hpp>

#include <StraveEngine/System/ExceptionHandler.hpp>
#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/Component/Transform.hpp>
#include <StraveEngine/Component/Mesh.hpp>
#include <StraveEngine/UI/UserInterfaceContainer.hpp>
#include <StraveEngine/Control/Mouse.hpp>
#include <StraveEngine/Renderer/Renderer.hpp>


namespace Strave
{
	UserInterface::UserInterface(std::string name) :
		Object(name),
		m_Transform(new Transform(this->m_Mesh)),
		m_Mesh(new Mesh(MeshType::RectangleSprite, this->m_Transform)),
		m_ShowState(true)
	{
		ExceptionHandler::Handle(UserInterfaceContainer::Insert(*this, this->m_KEY));
	}

	UserInterface::UserInterface(UserInterface& ui) :
		Object(ui),
		m_Transform(new Transform(this->m_Mesh)),
		m_Mesh(new Mesh(MeshType::RectangleSprite, this->m_Transform)),
		m_ShowState(ui.m_ShowState)
	{
		ExceptionHandler::Handle(UserInterfaceContainer::Insert(*this, this->m_KEY));

		m_Transform->SetPosition(ui.GetComponent<Transform>().GetPosition());
		m_Transform->SetScale(ui.GetComponent<Transform>().GetScale());
		m_Transform->SetRotation(ui.GetComponent<Transform>().GetRotation());
	}

	bool UserInterface::MouseClick(Mouse::Button button) const 
	{
		if (this->m_ShowState == true)
			return Mouse::Click(button, *this);
	
		return false; 
	}
	
	bool UserInterface::MouseDoubleClick(Mouse::Button button) const 
	{
		if (this->m_ShowState == true) 
			return Mouse::DoubleClick(button, *this);
	
		return false;
	}
	
	bool UserInterface::MouseDoubleClick(Mouse::Button button, float clickDelay) const 
	{
		if (this->m_ShowState == true)
			return Mouse::DoubleClick(button, clickDelay, *this);
	
		return false;
	}
	
	bool UserInterface::MouseReleased(Mouse::Button button) const 
	{
		if (this->m_ShowState == true)
			return Mouse::Released(button, *this);
	
		return false;
	}
	
	bool UserInterface::MouseHold(Mouse::Button button) const 
	{
		if (this->m_ShowState == true)
			return Mouse::Hold(button);
	
		return false;
	}
	
	bool UserInterface::MouseHover(void) 
	{
		if (this->m_ShowState == true)
			return Mouse::Hover(*this);
	
		return false;
	}
	
	bool UserInterface::MouseDrag(void) 
	{
		if (this->m_ShowState == true)
			return Mouse::Drag(*this);
	
		return false;
	}

	void UserInterface::Draw(void) const
	{
		Renderer::Draw(this->GetComponent<Mesh>());
	}
}
