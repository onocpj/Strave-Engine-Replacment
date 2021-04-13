#include <StraveEngine/Component/CameraContainer.hpp>

#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/System/MapContainer.cpp>


namespace Strave
{
	CameraContainer* CameraContainer::s_CameraContainer;

	void CameraContainer::Create(void)
	{
		CameraContainer::s_CameraContainer = new CameraContainer();
	}

	Exception CameraContainer::Delete(void)
	{
		try
		{
			delete CameraContainer::s_CameraContainer;
			CameraContainer::s_CameraContainer = nullptr;
		}
		catch (...)
		{
			return THROW__EXC_MAPC_RMV;
		}

		return NO_EXCEPTION;
	}

	Exception CameraContainer::Insert(const Camera& camera, Uint64& camKey)
	{
		SV_CORE_TRACE("Call from camera container");
		camKey = CameraContainer::s_CameraContainer->InsertToContainerRecycled(camera);

		return NO_EXCEPTION;
	}

	Exception CameraContainer::Erase(const Uint64& goKey)
	{
		SV_CORE_TRACE("Call from camera container");
		return CameraContainer::s_CameraContainer->EraseFromContainer(goKey);
	}
}
