#include <StraveEngine/Utility/Matrix.hpp>


namespace Strave
{
	Vector2u Matrix::IndexToPosition(Uint64 index, Vector2u dimensions)
	{
		Vector2u indexPosition = UNDEF_VECTOR2U;
		int matrixSize = dimensions.x * dimensions.y;

		if ((index + 1) <= matrixSize)
		{
			unsigned int row = 0;
			unsigned int column = 0;

			for (Uint64 i = 0; i < matrixSize - (matrixSize - index); i++)
			{
				column++;

				if ((i + 1) % dimensions.y == 0)
				{
					column = 0;
					row++;
				}
			}

			indexPosition = { column, row };
		}

		return indexPosition;
	}

	Uint32 Matrix::PositionToIndex(Vector2u dimensions)
	{
		Uint32 index = UINT64_ERROR_TYPE;
		Uint32 matrixSize = dimensions.x * dimensions.y;

		Uint32 row = 0;
		Uint32 column = 0;

		for (Uint32 i = 0; index < matrixSize; i++)
		{
			column++;

			if ((i + 1) % dimensions.y == 0)
			{
				column = 0;
				row++;
			}
		}

		index = row * dimensions.x + column;

		return index;
	}
}
