#include <StraveEngine/UI/UserInterfaceContainer.hpp>

#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/MapContainer.cpp>
#include <StraveEngine/UI/UserInterface.hpp>


namespace Strave
{
	UserInterfaceContainer* UserInterfaceContainer::s_UserInterfaceContainer;

	void UserInterfaceContainer::Create(void)
	{
		UserInterfaceContainer::s_UserInterfaceContainer = new UserInterfaceContainer();
	}

	Exception UserInterfaceContainer::Delete(void)
	{
		try
		{
			delete UserInterfaceContainer::s_UserInterfaceContainer;
			UserInterfaceContainer::s_UserInterfaceContainer = nullptr;
		}
		catch (...)
		{
			return THROW__EXC_GBC_DEL;
		}

		return NO_EXCEPTION;
	}

	Exception UserInterfaceContainer::Insert(const UserInterface& ui, Uint64& uiKey)
	{
		SV_CORE_TRACE("Call from object container");
		uiKey = UserInterfaceContainer::s_UserInterfaceContainer->InsertToContainerRecycled(ui);

		return NO_EXCEPTION;
	}

	Exception UserInterfaceContainer::Erase(const Uint64& uiKey)
	{
		SV_CORE_TRACE("Call from object container");
		return UserInterfaceContainer::s_UserInterfaceContainer->EraseFromContainer(uiKey);
	}
}
