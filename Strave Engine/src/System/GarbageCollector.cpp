#include <StraveEngine/System/GarbageCollector.hpp>

#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/ICollectable.hpp>
#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/System/MapContainer.cpp>

#include <vector>


namespace Strave
{
	GarbageCollector* GarbageCollector::s_GarbageCollector;

	Exception DeepSweep(std::vector<ICollectable*>& buffer, Uint16 startIndex);
	state_t BufferEmpty(const std::vector<ICollectable*>& buffer);
	state_t BufferSizeChanged(std::vector<ICollectable*>& buffA, std::vector<ICollectable*>& buffB);

	////////////////////////////////////////////////////////////
	/// Garbage Collector
	////////////////////////////////////////////////////////////
	void GarbageCollector::Create(void)
	{
		GarbageCollector::s_GarbageCollector = new GarbageCollector();
	}

	Exception GarbageCollector::Delete(void)
	{
		try
		{
			delete GarbageCollector::s_GarbageCollector;
			GarbageCollector::s_GarbageCollector = nullptr;
		}
		catch (...)
		{
			return THROW__EXC_GBC_DEL;
		}

		return NO_EXCEPTION;
	}

	Exception GarbageCollector::SweepMemory(void)
	{
		Int64 collectorSize = GarbageCollector::s_GarbageCollector->GetSize();
		ICollectable* object = UNDEF_PTR;
		std::vector<ICollectable*> deepSweepBuffer;

		for (Int64 key = -1; key != (collectorSize - 1); key++)
		{
			object = GarbageCollector::s_GarbageCollector->Next(key);

			try
			{
				if (object != UNDEF_PTR)
				{
					delete object;
					object = nullptr;
				}
			}
			catch (...)
			{
				// In case exception was thrown while trying to delete object
				// insert this object to deep sweep buffer. All elements from deep
				// sweep buffer will be tried to be deleted in some order
				deepSweepBuffer.push_back(object);
			}
		}

		// If deep sweep buffer contains data
		if (!BufferEmpty(deepSweepBuffer))
			return DeepSweep(deepSweepBuffer, 0); // Try to sweep buffer and return for any exceptions (Recursive function)

		// Else no exception was thrown
		return NO_EXCEPTION;
	}

	Exception GarbageCollector::Insert(const ICollectable& collectable, Uint64& collKey)
	{
		SV_CORE_TRACE("Call from garbage collector");
		collKey = GarbageCollector::s_GarbageCollector->InsertToContainerRecycled(collectable);
		return NO_EXCEPTION;
	}

	Exception GarbageCollector::Erase(const Uint64& collKey)
	{
		SV_CORE_TRACE("Call from garbage collector");
		return GarbageCollector::s_GarbageCollector->EraseFromContainer(collKey);
	}

	Exception DeepSweep(std::vector<ICollectable*>& buffer, Uint16 startIndex)
	{
		std::vector<ICollectable*> subBuffer;
		ICollectable* object = UNDEF_PTR;

		// If startIndex is higher than 0, we need in the first place
		// fill subbuffer with all the elements from previous buffer 
		// till startIndex, because we would loose all elements from
		// buffer that are stored in buffer at lower index than start index
		for (Uint16 i = 0; i < startIndex; i++)
			subBuffer.push_back(buffer.at(i));

		for (Uint16 i = startIndex; i < buffer.size(); i++) 
		{
			object = buffer.at(i);

			try 
			{
				delete object;
				object = nullptr;
			}
			catch (...)
			{
				subBuffer.push_back(object);
			}
		}

		// Check if any element was removed from buffer
		if (BufferSizeChanged(buffer, subBuffer))
		{
			// If so, check if buffer contains any elements
			if (!BufferEmpty(subBuffer))
				// If buffer contains elements, try again to deep sweep
				return DeepSweep(subBuffer, 0);
		}
		// If size of buffer has not changed
		else 
		{
			// Chceck if current attempts are lower than buffer size
			// If attempts count is higher than buffer size that means
			// each element in buffer tried to be deleted as first in order
			// and it did not success
			if (startIndex <= buffer.size())
				// Try to deep sweep, but start from next element in buffer (startIndex)
				return DeepSweep(subBuffer, ++startIndex);
			else
				// In that case throw sweep memory exception, because memory
				// could not be removed in any order
				return THROW__EXC_GBC_SWEEP_MEM;
		}

		// Else no exception was thrown
		return NO_EXCEPTION;
	}

	state_t BufferEmpty(const std::vector<ICollectable*>& buffer)
	{
		return buffer.size() > 0 ? false : true;
	}

	state_t BufferSizeChanged(std::vector<ICollectable*>& buffA, std::vector<ICollectable*>& buffB)
	{
		return buffA > buffB ? true : false;
	}
}
