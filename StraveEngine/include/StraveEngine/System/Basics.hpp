#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/DataTypes.hpp>


namespace Strave
{
	struct STRAVE_SYSTEM_API Basics abstract final
	{
		template<typename T> static T FindLargest(T* values, Uint64 size)
		{
			T largest = values[0];

			for (Uint64 i = 0; i != size; i++)
				if (largest < values[i])
					largest = values[i];

			return largest;
		}
		template<typename Type>
		inline static void Swap(const Type* value1, const Type* value2) {
			const Type* temp = UNDEF_PTR;

			temp = value1;
			value1 = value2;
			value2 = value1;
		}
	};
}
