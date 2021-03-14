#ifndef MATRIX_B
#define MATRIX_B

#include "Matrix.h"

inline Matrix3 operator+(const Matrix3& self, const Matrix3& other)
{
	return
	{	// 		colum 1					colum 2					colum 3				
		(self.p11 + other.p11), (self.p12 + other.p12), (self.p13 + other.p13), // row 1
		(self.p21 + other.p21), (self.p22 + other.p22), (self.p23 + other.p23), // row 2
		(self.p31 + other.p31), (self.p32 + other.p32), (self.p33 + other.p33), // row 3
	};
}

inline Matrix3 operator-(const Matrix3& self, const Matrix3& other)
{
	return
	{	// colum 1				colum 2				colum 3				
		(self.p11 - other.p11), (self.p12 - other.p12), (self.p13 - other.p13), // row 1
		(self.p21 - other.p21), (self.p22 - other.p22), (self.p23 - other.p23), // row 2
		(self.p31 - other.p31), (self.p32 - other.p32), (self.p33 - other.p33), // row 3
	};
}

inline Matrix3 operator*(const Matrix3& self, const f32 scalar)
{
	Matrix3 matrix;
	for (i8 i = 0; i < 9; i++)
	{
		matrix.mArray[i] = self.mArray[i] * scalar;
	}

	return matrix;
}

inline Matrix3 operator*(const Matrix3& self, const Matrix3& other)
{
	Matrix3 mat;
	mat.p11 = self.p11 * other.p11 + self.p12 * other.p21 + self.p13 * other.p31;
	mat.p12 = self.p11 * other.p12 + self.p12 * other.p22 + self.p13 * other.p32;
	mat.p13 = self.p11 * other.p13 + self.p12 * other.p23 + self.p13 * other.p33;

	mat.p21 = self.p21 * other.p11 + self.p22 * other.p21 + self.p23 * other.p31;
	mat.p22 = self.p21 * other.p12 + self.p22 * other.p22 + self.p23 * other.p32;
	mat.p23 = self.p21 * other.p13 + self.p22 * other.p23 + self.p23 * other.p33;

	mat.p31 = self.p31 * other.p11 + self.p32 * other.p21 + self.p33 * other.p31;
	mat.p32 = self.p31 * other.p12 + self.p32 * other.p22 + self.p33 * other.p32;
	mat.p33 = self.p31 * other.p13 + self.p32 * other.p23 + self.p33 * other.p33;

	return mat;
}

inline f32 GetDeterminant(const Matrix3& matrix)
{
	// we chose get the determinant with first column

	f32 firstRow = matrix.p11 * ((matrix.p22 * matrix.p33) - (matrix.p23 * matrix.p32));
	f32 secondRow = matrix.p21 * ((matrix.p12 * matrix.p33) - (matrix.p13 * matrix.p32));
	f32 thirdRow = matrix.p31 * ((matrix.p12 * matrix.p23) - (matrix.p13 * matrix.p22));

	return firstRow - secondRow + thirdRow;
}

inline Matrix3 GetTransposedMatrix(const Matrix3& matrix)
{
	return {
		matrix.p11, matrix.p21, matrix.p31,
		matrix.p12, matrix.p22, matrix.p32,
		matrix.p13, matrix.p23, matrix.p33,
	};
}

inline Matrix4 operator+(const Matrix4& self, const Matrix4& other)
{
	return
	{	// 		colum 1					colum 2					colum 3					colum 4
		(self.p11 + other.p11), (self.p12 + other.p12), (self.p13 + other.p13), (self.p14 + other.p14), // row 1
		(self.p21 + other.p21), (self.p22 + other.p22), (self.p23 + other.p23), (self.p24 + other.p24), // row 2
		(self.p31 + other.p31), (self.p32 + other.p32), (self.p33 + other.p33), (self.p34 + other.p34), // row 3
		(self.p41 + other.p41), (self.p42 + other.p42), (self.p43 + other.p43), (self.p44 + other.p44), // row 4
	};
}

inline Matrix4 operator-(const Matrix4& self, const Matrix4& other)
{
	return
	{	// 		colum 1					colum 2					colum 3					colum 4
		(self.p11 - other.p11), (self.p12 - other.p12), (self.p13 - other.p13), (self.p14 - other.p14), // row 1
		(self.p21 - other.p21), (self.p22 - other.p22), (self.p23 - other.p23), (self.p24 - other.p24), // row 2
		(self.p31 - other.p31), (self.p32 - other.p32), (self.p33 - other.p33), (self.p34 - other.p34), // row 3
		(self.p41 - other.p41), (self.p42 - other.p42), (self.p43 - other.p43), (self.p44 - other.p44), // row 4
	};
}

inline Matrix4 operator*(const Matrix4& self, const f32 scalar)
{
	Matrix4 matrix;
	for (i8 i = 0; i < 16; i++)
	{
		matrix.mArray[i] = self.mArray[i] * scalar;
	}

	return matrix;
}

inline Matrix4 operator/(const Matrix4& self, const f32 scalar)
{
	Matrix4 matrix;
	for (i8 i = 0; i < 16; i++)
	{
		matrix.mArray[i] = self.mArray[i] / scalar;
	}

	return matrix;
}

inline Matrix4 operator*(const Matrix4& self, const Matrix4& other)
{
	Matrix4 mat;
	mat.p11 = self.p11 * other.p11 + self.p12 * other.p21 + self.p13 * other.p31 + self.p14 * other.p41;
	mat.p12 = self.p11 * other.p12 + self.p12 * other.p22 + self.p13 * other.p32 + self.p14 * other.p42;
	mat.p13 = self.p11 * other.p13 + self.p12 * other.p23 + self.p13 * other.p33 + self.p14 * other.p43;
	mat.p14 = self.p11 * other.p14 + self.p12 * other.p24 + self.p13 * other.p34 + self.p14 * other.p44;

	mat.p21 = self.p21 * other.p11 + self.p22 * other.p21 + self.p23 * other.p31 + self.p24 * other.p41;
	mat.p22 = self.p21 * other.p12 + self.p22 * other.p22 + self.p23 * other.p32 + self.p24 * other.p42;
	mat.p23 = self.p21 * other.p13 + self.p22 * other.p23 + self.p23 * other.p33 + self.p24 * other.p43;
	mat.p24 = self.p21 * other.p14 + self.p22 * other.p24 + self.p23 * other.p34 + self.p24 * other.p44;

	mat.p31 = self.p31 * other.p11 + self.p32 * other.p21 + self.p33 * other.p31 + self.p34 * other.p41;
	mat.p32 = self.p31 * other.p12 + self.p32 * other.p22 + self.p33 * other.p32 + self.p34 * other.p42;
	mat.p33 = self.p31 * other.p13 + self.p32 * other.p23 + self.p33 * other.p33 + self.p34 * other.p43;
	mat.p34 = self.p31 * other.p14 + self.p32 * other.p24 + self.p33 * other.p34 + self.p34 * other.p44;

	mat.p41 = self.p41 * other.p11 + self.p42 * other.p21 + self.p43 * other.p31 + self.p44 * other.p41;
	mat.p42 = self.p41 * other.p12 + self.p42 * other.p22 + self.p43 * other.p32 + self.p44 * other.p42;
	mat.p43 = self.p41 * other.p13 + self.p42 * other.p23 + self.p43 * other.p33 + self.p44 * other.p43;
	mat.p44 = self.p41 * other.p14 + self.p42 * other.p24 + self.p43 * other.p34 + self.p44 * other.p44;

	return mat;
}

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

inline Matrix4 GetTransposedMatrix(const Matrix4& matrix)
{
	return {
		matrix.p11, matrix.p21, matrix.p31, matrix.p41,
		matrix.p12, matrix.p22, matrix.p32, matrix.p42,
		matrix.p13, matrix.p23, matrix.p33, matrix.p43,
		matrix.p14, matrix.p24, matrix.p34, matrix.p44,
	};
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



#endif // MATRIX_B