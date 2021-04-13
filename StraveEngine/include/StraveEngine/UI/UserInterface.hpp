#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/Entity/Object.hpp>


namespace Strave
{
	class Mesh;
	class Transform;

	class STRAVE_UI_API UserInterface abstract final : public Object
	{
	public:
		UserInterface();
		UserInterface(std::string name);
		UserInterface(UserInterface& ui);
		~UserInterface() = default;

		template<typename T> inline T& GetComponent(void) const;
		template<> inline Mesh& GetComponent<Mesh>(void) const { return *m_Mesh; }
		inline void Show(void) { m_ShowState = true; }
		inline void Hide(void) { m_ShowState = false; }

	private:
		Uint64		m_KEY;
		Mesh*		m_Mesh;
		Transform*	m_Transform;
		bool		m_ShowState;
	};
}

