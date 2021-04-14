#pragma once

#include <StraveEngine/System/MapContainer.hpp>
#include <StraveEngine/Renderer/Renderer.hpp>


namespace Strave
{
	struct Exception;
	class Animation;

	class AnimationContainer final : public MapContainer<Animation>
	{
	private:
		friend Animation;

	public:
		static void Create(void);
		static Exception Delete(void);
		inline static Uint64 GetObjectContainerSize(void) { return s_AnimationContainer->GetSize(); }

	private:
		AnimationContainer() = default;
		~AnimationContainer() = default;
		AnimationContainer(const AnimationContainer&) = delete;

		friend const Animation* Renderer::PullAnimationFromContainer(Uint64 key);

	protected:
		static Exception Insert(const Animation& animation, Uint64 & animKey);
		static Exception Erase(const Uint64 & animKey);

	private:
		static AnimationContainer* s_AnimationContainer;
	};
}
