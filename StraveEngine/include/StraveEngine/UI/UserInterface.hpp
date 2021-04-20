#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/Entity/Object.hpp>
#include <StraveEngine/Control/Mouse.hpp>


namespace Strave
{
	class Mouse;
	class Mesh;
	class Transform;
	class Renderer;
	class Texture;

	enum class UIType
	{
		Undefined = 0,
		Cell,
		Grid,
		Button,
		TextBox,
		CheckBox,
		Label,
		Slider
	};

	class STRAVE_UI_API UserInterface abstract : public Object
	{
	public:
		UserInterface(std::string name = EMPTY_STR);
		UserInterface(UserInterface& ui);
		~UserInterface() = default;

		virtual UIType GetType(void) const = 0;
		template<typename T> inline T& GetComponent(void) const;
		template<> inline Mesh& GetComponent<Mesh>(void) const { return *m_Mesh; }
		template<> inline Transform& GetComponent<Transform>(void) const { return *m_Transform; }
		inline bool IsVisible(void) const { return m_ShowState; }
		inline virtual void Show(void) { m_ShowState = true; }
		inline virtual void Hide(void) { m_ShowState = false; }

		virtual bool MouseClick(Mouse::Button button) const;
		virtual bool MouseDoubleClick(Mouse::Button button) const;
		virtual bool MouseDoubleClick(Mouse::Button button, float clickDelay) const;
		virtual bool MouseReleased(Mouse::Button button) const;
		virtual bool MouseHold(Mouse::Button button) const;
		virtual bool MouseHover(void);
		virtual bool MouseDrag(void);

	protected:
		virtual void Draw(void) const;

	protected:
		Uint64			m_KEY;
		Mesh*			m_Mesh;
		Transform*		m_Transform;
		bool			m_ShowState;
	};
}

