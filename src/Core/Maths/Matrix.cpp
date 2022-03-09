#include "Matrix.h"


f32 GetDeterminantOfCell(const Matrix4& matrix, i8 rowToExclud, i8 columnToExclud)
{
	Matrix3 subMatrix;
	i8 currentCell = 0;

	for (i8 i = 0; i < 4; i++)
	{
		if (i != rowToExclud)
		{
			for (i8 j = 0; j < 4; j++)
			{
				if (j != columnToExclud)
				{
					// TODO: revise if matrix is created with correctly position/value
					subMatrix.mArray[currentCell] = matrix.mMatrix[i][j];
				}
			}
		}
	}

	return GetDeterminant(subMatrix);
}

f32 GetDeterminant(const Matrix4& matrix)
{
	// we chose get the determinant with first column

	f32 firstDeterminant;

	{
		Matrix3 firstMat =
		{
			matrix.p22, matrix.p23, matrix.p24,
			matrix.p32, matrix.p33, matrix.p34,
			matrix.p42, matrix.p43, matrix.p44
		};

		firstDeterminant = matrix.p11 * GetDeterminant(firstMat);
	}

	f32 secondDeterminant;

	{
		Matrix3 secondMat =
		{
			matrix.p12, matrix.p13, matrix.p14,
			matrix.p32, matrix.p33, matrix.p34,
			matrix.p42, matrix.p43, matrix.p44
		};

		secondDeterminant = matrix.p21 * GetDeterminant(secondMat);
	}

	f32 thirdDeterminant;

	{
		Matrix3 thirdMat =
		{
			matrix.p12, matrix.p13, matrix.p14,
			matrix.p22, matrix.p23, matrix.p24,
			matrix.p42, matrix.p43, matrix.p44
		};

		thirdDeterminant = matrix.p31 * GetDeterminant(thirdMat);
	}


	f32 fourthDeterminant;

	{
		Matrix3 fourthMat =
		{
			matrix.p12, matrix.p13, matrix.p14,
			matrix.p22, matrix.p23, matrix.p24,
			matrix.p32, matrix.p33, matrix.p34,
		};

		fourthDeterminant = matrix.p41 * GetDeterminant(fourthMat);
	}


	return firstDeterminant - secondDeterminant + thirdDeterminant - fourthDeterminant;
}



Matrix4 GetAdjointMatrix(const Matrix4& matrix)
{
	i8 multiplier = 1;
	Matrix4 adjointMatrix;
	for (i8 i = 0; i < 4; i++)
	{
		for (i8 j = 0; j < 4; j++)
		{

			adjointMatrix.mMatrix[i][j] = multiplier * GetDeterminantOfCell(matrix, i, j);

			multiplier *= -1;
		}
	}
	return adjointMatrix;
}

Matrix4 GetInverseMatrix(const Matrix4& matrix)
{
	Matrix4 transposedMatrix = GetTransposedMatrix(matrix);

	return GetAdjointMatrix(transposedMatrix) / GetDeterminant(matrix);
}