#include <StraveEngine/System/MapContainer.hpp>

#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/System/Exception.hpp>


namespace Strave
{
	////////////////////////////////////////////////////////////
	/// Map Container
	////////////////////////////////////////////////////////////
	template<typename T>
	T* MapContainer<T>::GetElement(const Uint64 key) const
	{
		return const_cast<T*>(m_Container.at(key));
	}
	template<typename T>
	T* MapContainer<T>::Next(const Int64 currentKey) const
	{
		Int64 next = currentKey + 1;

		if (this->Contains((Uint64)next))
			return this->GetElement((Uint64)next);

		return UNDEF_PTR;
	}

	template<typename T>
	T* MapContainer<T>::Previous(const Int64 currentKey) const
	{
		Int64 next = currentKey - 1;

		if (this->Contains((Uint64)next))
			return this->GetElement((Uint64)next);

		return UNDEF_PTR;
	}

	template<typename T>
	bool MapContainer<T>::IsEmpty(void) const
	{
		if (m_Container.size() == 0)
			return MC_EMPTY;
		
		return !MC_EMPTY;
	}

	template<typename T>
	bool MapContainer<T>::Contains(const T& obj) const
	{
		if (m_Container.size() > 0) {
			for (auto iter = m_Container.begin(), end = m_Container.end(); iter != end; ++iter) {
				if (iter->second == &obj) {
					return true;
				}
			}
		}

		return false;
	}

	template<typename T>
	bool MapContainer<T>::Contains(const Uint64 key) const
	{
		if (key < m_Container.size()) {
			if (m_Container.at(key) != UNDEF_PTR)
				return true;
		}

		return false;
	}
	
	template<typename T>
	Int64 MapContainer<T>::InsertToContainer(const T& obj)
	{
		Int64 assignedID = m_ID.AssignID(*this, obj);

		if (assignedID != MC_UNDEF_KEY)
		{
			m_Container.insert(std::pair<Uint64, const T*>((Uint64)assignedID, &obj));
			SV_CORE_TRACE("function InsertToContainer from MapContainer: element pushed to container");
		}
		else 
		{
			SV_CORE_WARN("function InsertToContainer from MapContainer: unable to insert element to container");
		}

		return assignedID;
	}
	
	template<typename T>
	Int64 MapContainer<T>::InsertToContainerRecycled(const T& obj)
	{
		Int64 assignedID = MC_UNDEF_KEY;

		if (!IsKeyHolderEmpty())
		{
			Uint64 keyFromHolder = GetKeyFromHolder();
			auto element = m_Container.find(keyFromHolder);

			element->second = &obj;
			assignedID = keyFromHolder;

			SV_CORE_TRACE("function InsertToContainerRecycled from MapContainer: element pushed to container");
		}
		else 
			assignedID = MapContainer::InsertToContainer(obj);

		return assignedID;
	}
	
	template<typename T>
	Exception MapContainer<T>::EraseFromContainer(const Uint64 key)
	{
		if (m_ID.IsInRange(key))
		{
			auto element = m_Container.find(key);
			PassKeyToHolder(key);

			element->second = UNDEF_PTR;

			SV_CORE_TRACE("function EraseFromContainer from MapContainer: Element erased from container");
		}
		else 
		{
			// SV_CORE_WARN(THROW__EXC_MAPC_RMV[EXC_MSG]);
			return THROW__EXC_MAPC_RMV;
		}

		return NO_EXCEPTION;
	}
	
	template<typename T>
	void MapContainer<T>::PassKeyToHolder(Uint64 key)
	{
		m_EmptyKeyHolder.push(key);
	}
	
	template<typename T>
	Int64 MapContainer<T>::GetKeyFromHolder(void)
	{
		if (!IsKeyHolderEmpty())
		{
			Int64 popedKey = (Int64)m_EmptyKeyHolder.top();
			m_EmptyKeyHolder.pop();

			return popedKey;
		}
		else 
		{
			return MC_UNDEF_KEY;
		}
	}
	
	template<typename T>
	bool MapContainer<T>::IsKeyHolderEmpty(void)
	{
		if (m_EmptyKeyHolder.size() > 0)
			return false;
		else
			return true;
	}
	
	template<typename T>
	bool MapContainer<T>::IsKeyInRange(Uint64 key)
	{
		if (key < this->GetSize())
			return true;
		else
			return false;
	}

	////////////////////////////////////////////////////////////
	/// Identifier
	////////////////////////////////////////////////////////////
	template<typename T>
	Int64 MapContainer<T>::Identifier::AssignID(MapContainer& bc, const T& obj)
	{
		if (!bc.Contains(obj))
		{
			return ++Key;
		}

		return MC_UNDEF_KEY;
	}

	template<typename T>
	bool MapContainer<T>::Identifier::IsInRange(Uint64 key)
	{
		if (key <= Key)
			return true;
		else
			return false;
	}
}
