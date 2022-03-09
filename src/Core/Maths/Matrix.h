#ifndef MATRIX_H
#define MATRIX_H

#include "MathDef.h"

union Matrix3
{
	f32 mArray[9];
	f32 mMatrix[3][3];
	struct
	{
		f32 p11; f32 p12; f32 p13;
		f32 p21; f32 p22; f32 p23;
		f32 p31; f32 p32; f32 p33;
	};

	Matrix3(){};
 
	Matrix3(f32 const p11Value, f32 const p12Value, f32 const p13Value,
			f32 const p21Value, f32 const p22Value, f32 const p23Value,
			f32 const p31Value, f32 const p32Value, f32 const p33Value)

			:  p11(p11Value), p12(p12Value), p13(p13Value),
			   p21(p21Value), p22(p22Value), p23(p23Value),
			   p31(p31Value), p32(p32Value), p33(p33Value)
	{};

	Matrix3(f32 const value)
	{
		p11 = p22 = p33 = value;

		p12 = p13 = p21 = p23 = p31 = p32 = 0.0f;
	};

	Matrix3(Matrix3 const &other);
};

union Matrix4
{
	f32 mArray[16];
	f32 mMatrix[4][4];
	struct
	{
		f32 p11; f32 p12; f32 p13; f32 p14;
		f32 p21; f32 p22; f32 p23; f32 p24;
		f32 p31; f32 p32; f32 p33; f32 p34;
		f32 p41; f32 p42; f32 p43; f32 p44;
	};

	Matrix4(){};

	Matrix4(f32 const p11Value, f32 const p12Value, f32 const p13Value, f32 const p14Value,
			f32 const p21Value, f32 const p22Value, f32 const p23Value, f32 const p24Value,
			f32 const p31Value, f32 const p32Value, f32 const p33Value, f32 const p34Value,
			f32 const p41Value, f32 const p42Value, f32 const p43Value, f32 const p44Value )

			:  p11(p11Value), p12(p12Value), p13(p13Value), p14(p14Value),
			   p21(p21Value), p22(p22Value), p23(p23Value), p24(p24Value),
			   p31(p31Value), p32(p32Value), p33(p33Value), p34(p34Value),
			   p41(p41Value), p42(p42Value), p43(p43Value), p44(p44Value)
	{};

	Matrix4(f32 const value)
	{
		p11 = p22 = p33 = p44 = value;

		p12 = p13 = p14 = p21 = p23 = p24 = p31 = p32 = p34 = p41 = p42 = p43 = 0.0f;
	};

};


// ---------------------------- Matrix3 ----------------------------------
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

// ---------------------------- Matrix4 ----------------------------------


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

inline Matrix4 GetTransposedMatrix(const Matrix4& matrix)
{
	return {
		matrix.p11, matrix.p21, matrix.p31, matrix.p41,
		matrix.p12, matrix.p22, matrix.p32, matrix.p42,
		matrix.p13, matrix.p23, matrix.p33, matrix.p43,
		matrix.p14, matrix.p24, matrix.p34, matrix.p44,
	};
}

f32 GetDeterminantOfCell(const Matrix4& matrix, i8 rowToExclud, i8 columnToExclud);

f32 GetDeterminant(const Matrix4& matrix);

Matrix4 GetAdjointMatrix(const Matrix4& matrix);

Matrix4 GetInverseMatrix(const Matrix4& matrix);

#endif // MATRIX_H