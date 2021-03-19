#pragma once

#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include "StraveEngine/System/Export.hpp"

#include <map>
#include <stack>


#define MC_UNDEF_KEY	ERROR_TYPE
#define MC_EMPTY		!UNDEF_BOOL


namespace Strave
{
	struct Exception;

	template<typename T>
	class STRAVE_SYSTEM_API MapContainer
	{
	private:
		struct Identifier
		{
			inline Identifier() : Key(MC_UNDEF_KEY) {}
			Identifier(const Identifier&) = delete;

			Int64 AssignID(MapContainer& bc, const T& obj);
			bool IsInRange(Uint64 key);

			Uint64 Key;
		};

	public:
		MapContainer() = default;
		~MapContainer() = default;
		MapContainer(const MapContainer&) = default;

		inline Uint64 GetSize(void) const { return m_Container.size(); }
		T* GetElement(const Uint64 key) const;
		T* Next(const Int64 currentKey) const;
		T* Previous(const Int64 currentKey) const;
		bool IsEmpty(void) const;
		bool Contains(const T& obj) const;
		bool Contains(const Uint64 key) const;
		Int64 InsertToContainer(const T& obj);
		Int64 InsertToContainerRecycled(const T& obj);
		Exception EraseFromContainer(const Uint64 key);

	private:
		void PassKeyToHolder(Uint64 key);
		Int64 GetKeyFromHolder(void);
		bool IsKeyHolderEmpty(void);
		bool IsKeyInRange(Uint64 key);

	private:
		Identifier					m_ID;
		std::map<Uint64, const T*>	m_Container;
		std::stack<Uint64>			m_EmptyKeyHolder;
	};
}
