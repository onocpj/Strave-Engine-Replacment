#pragma once


#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/DataTypes.hpp>

#include <vector>
#include <queue>


namespace Strave
{
	struct STRAVE_SYSTEM_API Array abstract final
	{
		template<typename Type>
		inline static void EraseElementsFromVector(std::vector<Type>& myVec, std::queue<unsigned int>& atIndex) 
		{
			unsigned int t_VecSize;
			unsigned int t_Index;

			t_VecSize = (unsigned int)myVec.size();
			t_Index = 0;

			while (!atIndex.empty()) 
			{
				t_Index = atIndex.front();
				atIndex.pop();

				if (t_VecSize <= t_Index)
					myVec.erase(myVec.begin() + t_Index);
			}
		}
		template<typename Type>
		inline static void EraseElementsFromVector(std::vector<Type>& myVec, unsigned int atIndex) 
		{
			unsigned int t_VecSize;

			t_VecSize = (unsigned int)myVec.size();

			if (t_VecSize <= atIndex)
				myVec.erase(myVec.begin() + atIndex);
		}
		template<typename Type>
		inline static int CopyArray(const Type*& from, Type*& to, Uint64 size) 
		{
			try 
			{
				for (Uint64 index = 0; index != size; index++)
					to[index] = from[index];

				return 0;
			}
			catch (...) 
			{
				return -1;
			}
		}
		template<typename Type, size_t size>
		inline static int CopyArray(const std::array<Type, size>& from, std::array<Type, size>& to)
		{
			try 
			{
				for (Uint64 index = 0; index != size; index++)
					to[index] = from[index];

				return 0;
			}
			catch (...) 
			{
				return -1;
			}
		}
	};
}
