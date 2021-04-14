#include <StraveEngine/Component/Animation/AnimationContainer.hpp>

#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/MapContainer.cpp>
#include <StraveEngine/Component/Animation/Animation.hpp>


namespace Strave
{
	AnimationContainer* AnimationContainer::s_AnimationContainer;

	void AnimationContainer::Create(void)
	{
		AnimationContainer::s_AnimationContainer = new AnimationContainer();
	}

	Exception AnimationContainer::Delete(void)
	{
		try
		{
			delete AnimationContainer::s_AnimationContainer;
			AnimationContainer::s_AnimationContainer = nullptr;
		}
		catch (...)
		{
			return THROW__EXC_GBC_DEL;
		}

		return NO_EXCEPTION;
	}

	Exception AnimationContainer::Insert(const Animation& animation, Uint64& animKey)
	{
		SV_CORE_TRACE("Call from object container");
		animKey = AnimationContainer::s_AnimationContainer->InsertToContainerRecycled(animation);

		return NO_EXCEPTION;
	}

	Exception AnimationContainer::Erase(const Uint64& animKey)
	{
		SV_CORE_TRACE("Call from object container");
		return AnimationContainer::s_AnimationContainer->EraseFromContainer(animKey);
	}
}

