#pragma once

#include <StraveEngine/System/MapContainer.hpp>
#include <StraveEngine/Renderer/Renderer.hpp>


namespace Strave
{
	struct Exceptions;
	class UserInterface;
	class Grid;

	class UserInterfaceContainer final : public MapContainer<UserInterface>
	{
	private:
		friend UserInterface;
		friend Grid;

	public:
		static void Create(void);
		static Exception Delete(void);
		inline static Uint64 GetUserInterfaceContainerSize(void) { return s_UserInterfaceContainer->GetSize(); }

	private:
		UserInterfaceContainer() = default;
		~UserInterfaceContainer() = default;
		UserInterfaceContainer(const UserInterfaceContainer&) = delete;

		friend const UserInterface* Renderer::PullUserInterfaceFromContainer(Uint64 key);

	protected:
		static Exception Insert(const UserInterface& ui, Uint64 & uiKey);
		static Exception Erase(const Uint64 & uiKey);

	private:
		static UserInterfaceContainer* s_UserInterfaceContainer;
	};
}

