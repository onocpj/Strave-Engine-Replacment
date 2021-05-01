#include <StraveEngine/UI/UserInterface.hpp>

#include <StraveEngine/Component/Transform.hpp>
#include <StraveEngine/Component/Mesh.hpp>
#include <StraveEngine/Control/Mouse.hpp>
#include <StraveEngine/Renderer/Renderer.hpp>
#include <StraveEngine/Component/Image.hpp>
#include <StraveEngine/Element/RectangleSprite.hpp>


namespace Strave
{
	UserInterface::UserInterface(std::string name) :
		Object(name),
		m_Transform(new Transform(&this->m_Image->GetSprite())), 
		m_Image(new Image(this->m_Transform)),
		m_ShowState(true)
	{}

	UserInterface::UserInterface(UserInterface& ui) :
		Object(ui),
		m_Transform(new Transform(&this->m_Image->GetSprite())),
		m_Image(new Image(this->m_Transform)),
		m_ShowState(ui.m_ShowState)
	{
		m_Transform->SetPosition(ui.GetComponent<Transform>().GetPosition());
		m_Transform->SetRotation(ui.GetComponent<Transform>().GetRotation());
		m_Image->SetNativeSize(ui.m_Image->GetNativeSize());
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
		Renderer::Draw(this->GetComponent<Image>());
	}
}
