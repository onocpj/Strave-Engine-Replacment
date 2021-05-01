#include <StraveEngine/Entity/GameObjectContainer.hpp>

#include <StraveEngine/Entity/GameObject.hpp>
#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/MapContainer.cpp>


namespace Strave
{
	GameObjectContainer* GameObjectContainer::s_GameObjectContainer;

	void GameObjectContainer::Create(void)
	{
		GameObjectContainer::s_GameObjectContainer = new GameObjectContainer();
	}

	Exception GameObjectContainer::Delete(void)
	{
		try
		{
			delete GameObjectContainer::s_GameObjectContainer;
			GameObjectContainer::s_GameObjectContainer = nullptr;
		}
		catch (...)
		{
			return THROW__EXC_GBC_DEL;
		}

		return NO_EXCEPTION;
	}

	Exception GameObjectContainer::Insert(const GameObject& gameObject, Uint64& goKey)
	{
		SV_CORE_TRACE("Call from object container");
		goKey = GameObjectContainer::s_GameObjectContainer->InsertToContainerRecycled(gameObject);

		return NO_EXCEPTION;
	}

	Exception GameObjectContainer::Erase(const Uint64& goKey)
	{
		SV_CORE_TRACE("Call from object container");
		return GameObjectContainer::s_GameObjectContainer->EraseFromContainer(goKey);
	}
}
