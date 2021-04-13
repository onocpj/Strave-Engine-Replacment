#pragma once

#include <StraveEngine/System/MapContainer.hpp>


namespace Strave
{
	struct Exception;
	class ICollectable;

	class GarbageCollector final : private MapContainer<ICollectable>
	{
	private:
		friend ICollectable;

	public:
		static void Create(void);
		static Exception Delete(void);
		static Exception SweepMemory(void);

	private:
		GarbageCollector() = default;
		~GarbageCollector() = default;
		GarbageCollector(const GarbageCollector&) = delete;

	protected:
		static Exception Insert(const ICollectable& collectable, Uint64& collKey);
		static Exception Erase(const Uint64& collKey);

	private:
		static GarbageCollector* s_GarbageCollector;
	};
}

