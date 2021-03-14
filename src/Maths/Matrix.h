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
		new (this) Matrix3 
		{
			value, 0.0f, 0.0f,
			0.0f, value, 0.0f,
			0.0f, 0.0f, value,
		};
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
		new (this) Matrix4 
		{
			value, 0.0f, 0.0f, 0.0f,
			0.0f, value, 0.0f, 0.0f,
			0.0f, 0.0f, value, 0.0f,
			0.0f, 0.0f, 0.0f, value
		};
	};

};

#endif // MATRIX_H