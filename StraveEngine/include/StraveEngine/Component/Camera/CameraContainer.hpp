#pragma once

#include <StraveEngine/System/MapContainer.hpp>
#include <StraveEngine/Renderer/Renderer.hpp>
#include <StraveEngine/Component/Camera/Camera.hpp>


namespace Strave
{
	class CameraContainer final : public MapContainer<Camera>
	{
	private:
		friend Camera;

	public:
		static void Create(void);
		static Exception Delete(void);
		inline static Uint64 GetCameraContainerCSize(void) { return s_CameraContainer->GetSize(); }

	private:
		CameraContainer() = default;
		~CameraContainer() = default;
		CameraContainer(const CameraContainer&) = delete;

		friend Camera* Renderer::PullCameraFromContainer(Uint64 key);
		friend Camera& Camera::GetCamera(Uint64 key);

	protected:
		static Exception Insert(const Camera& camera, Uint64& goKey);
		static Exception Erase(const Uint64& goKey);

	private:
		static CameraContainer* s_CameraContainer;
	};
}

