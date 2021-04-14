#pragma once

#include <StraveEngine/System/MapContainer.hpp>
#include <StraveEngine/Renderer/Renderer.hpp>


namespace Strave
{
	struct Exception;
	class GameObject;

	class GameObjectContainer final : public MapContainer<GameObject>
	{
	private:
		friend GameObject;

	public:
		static void Create(void);
		static Exception Delete(void);
		inline static Uint64 GetObjectContainerSize(void) { return s_GameObjectContainer->GetSize(); }

	private:
		GameObjectContainer() = default;
		~GameObjectContainer() = default;
		GameObjectContainer(const GameObjectContainer&) = delete;

		friend const GameObject* Renderer::PullObjectFromContainer(Uint64 key);

	protected:
		static Exception Insert(const GameObject& gameObject, Uint64 & goKey);
		static Exception Erase(const Uint64 & goKey);

	private:
		static GameObjectContainer* s_GameObjectContainer;
	};
}

