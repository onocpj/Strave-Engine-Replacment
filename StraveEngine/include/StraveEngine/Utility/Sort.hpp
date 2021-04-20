#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/DataTypes.hpp>

#include <vector>


namespace Strave
{
	struct STRAVE_SYSTEM_API Sort abstract final
	{
		template<typename Type>
		inline static void SelectionSort(std::vector<Type&>& arr)
		{
			Uint64 minIndex = 0;

			for (Uint64 i = 0; i != arr.size(); i++)
			{
				minIndex = i;

				for (Uint64 j = i + 1; j != arr.size(); j++)
					if (arr[j] < arr[minIndex])
						minIndex = j;

				std::swap(arr[minIndex], arr[i]);
			}
		}
	};
}
