#ifndef VECTOR_H
#define VECTOR_H

#include "MathDef.h"

union Vector3
{
	struct
	{
		f32 x;
		f32 y;
		f32 z;
	};

	struct
	{
		f32 r;
		f32 g;
		f32 b;
	};

	Vector3() {};

	Vector3(f32 const value)
	{
		new (this) Vector3{ value, value, value };
	};

	Vector3(f32 const xValue, f32 const yValue, f32 const zValue)
		: x(xValue), y(yValue), z(zValue)
	{}

};

struct Vector2
{
	f32 x;
	f32 y;
};

#endif //VECTOR_H
