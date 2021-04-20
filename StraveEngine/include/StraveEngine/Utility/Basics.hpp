#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/DataTypes.hpp>


namespace Strave
{
	struct STRAVE_SYSTEM_API Basics abstract final
	{
		template<typename T>
		inline static void Swap(const T* value1, const T* value2) {
			const T* temp = UNDEF_PTR;

			temp = value1;
			value1 = value2;
			value2 = value1;
		}
	};
}
