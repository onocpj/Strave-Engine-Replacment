#pragma once

#include <StraveEngine/System/DataTypes.hpp>


namespace Strave
{
	struct Math
	{
		template<typename T> static T FindLargest(T* values, Uint64 size)
		{
			T largest = values[0];

			for (Uint64 i = 0; i != size; i++)
				if (largest < values[i])
					largest = values[i];

			return largest;
		}
	};
}

