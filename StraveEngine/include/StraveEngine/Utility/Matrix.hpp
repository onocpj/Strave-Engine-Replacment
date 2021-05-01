#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/System/Vector2.hpp>


namespace Strave
{
	struct STRAVE_SYSTEM_API Matrix abstract
	{
		static Vector2u IndexToPosition(Uint64 index, Vector2u dimensions);
		static Uint32 PositionToIndex(Vector2u dimensions);
		template<typename T> static T* GetColumn(T* matrix, int columnIndex, Vector2u dimensions)
		{
			int matrixSize = dimensions.x * dimensions.y;

			if (matrix != nullptr && matrixSize > 0)
			{
				T* column = new T[dimensions.y];
				int rowIndex = 0;

				for (Uint64 i = 0; i < matrixSize; i++)
				{
					Vector2u elementPosition = IndexToPosition(i, dimensions);

					if (elementPosition.x == columnIndex)
					{
						column[rowIndex] = matrix[i]; 
						rowIndex++;						
					}
				}

				return column;
			}

			return nullptr;
		}
		template<typename T> static T* GetRow(T* matrix, int rowIndex, Vector2u dimensions)
		{
			int matrixSize = dimensions.x * dimensions.y;

			if (matrix != nullptr && matrixSize > 0)
			{
				T* row = new T[dimensions.x];
				int columnIndex = 0;

				for (Uint64 i = 0; i < matrixSize; i++)
				{
					Vector2u elementPosition = IndexToPosition(i, dimensions);

					if (elementPosition.y == rowIndex)
					{
						row[columnIndex] = matrix[i];
						columnIndex++;				
					}
				}

				return row;
			}

			return nullptr;
		}
		template<typename T> static T* FindHighestAverageColumn(T* matrix, Vector2u dimensions)
		{
			if (dimensions.x > 0)
			{
				T currentAverage = 0;
				T highestAverage = 0;
				Int64 highestAverageColumnIndex = -1;
				T* highestAverageColumn = new T[dimensions.y];

				for (Uint64 i = 0; i < dimensions.y; i++)
				{
					T* column = GetColumn<T>(matrix, i, dimensions);
					currentAverage = GetAverageFromColumn<T>(column, dimensions.x);

					if (highestAverage <= currentAverage)
						highestAverageColumn = column;
				}

				return highestAverageColumn;
			}

			return nullptr;
		}
		template<> static int* FindHighestAverageColumn<int>(int* matrix, Vector2u dimensions);
		template<> static float* FindHighestAverageColumn<float>(float* matrix, Vector2u dimensions);
		template<> static double* FindHighestAverageColumn<double>(double* matrix, Vector2u dimensions);
		template<typename T> static T GetAverageFromColumn(T* column, Uint64 columnSize)
		{
			if (column != NULL && columnSize > 0)
			{
				T average = 0;

				for (Uint64 i = 0; i < columnSize; i++)
					average += column[i];

				return average / columnSize;
			}

			return (T)NULL;
		}
		template<> static int GetAverageFromColumn<int>(int* column, Uint64 columnSize);
		template<> static float GetAverageFromColumn<float>(float* column, Uint64 columnSize);
		template<> static double GetAverageFromColumn<double>(double* column, Uint64 columnSize);
	};
}

