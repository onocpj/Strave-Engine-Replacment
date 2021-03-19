#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>


#define IC_ID_UNASSIGNED	ERROR_TYPE


namespace Strave
{
	struct Exception;
	class GarbageCollector;

	////////////////////////////////////////////////////////////
	// 
	//	Each objects memory position, that is derived from ICollectable,
	//	is tracked by engine and deleted automatically upon application end
	//
	////////////////////////////////////////////////////////////
	class STRAVE_SYSTEM_API ICollectable abstract
	{
	public:
		virtual ~ICollectable();

	protected:
		ICollectable();
		ICollectable(const ICollectable&) = default;

	private:
		Uint64 m_KEY = IC_ID_UNASSIGNED;
	};
}
