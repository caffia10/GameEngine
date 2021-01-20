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

inline Vector3 operator+(const Vector3& self, const Vector3& other)
{
	return {
		self.x + other.x, // X
		self.y + other.y, // Y
		self.z + other.z  // Z
	};
}

inline Vector3 operator-(const Vector3& self, const Vector3& other)
{
	return {
		self.x - other.x, // X
		self.y - other.y, // Y
		self.z - other.z  // Z
	};
}

inline Vector3 operator*(const Vector3& self, f32 scalar)
{
	return {
		self.x * scalar, // X
		self.y * scalar, // Y
		self.z * scalar  // Z
	};
}

inline Vector3 operator/(const Vector3& self, f32 scalar)
{
	return {
		self.x / scalar, // X
		self.y / scalar, // Y
		self.z / scalar  // Z
	};
}

//get magnitude of current vector, also called norm or legth 
inline f32 GetMagnitude(const Vector3& vector)
{
	return sqrtf(Square(vector.x) + Square(vector.y) + Square(vector.z));
}

inline f32 GetDotProduct(const Vector3& vectorA, const Vector3& vectorB)
{
	return (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y) + (vectorA.z * vectorB.z);
}

inline f32 GetAngle(const Vector3& vectorA, const Vector3& vectorB)
{
	f32 firstStepResult = GetDotProduct(vectorA, vectorB) / GetMagnitude(vectorA) * GetMagnitude(vectorB);
	return acosf(firstStepResult);
}

inline Vector3 GetCrossProduct(const Vector3& vectorA, const Vector3& vectorB)
{
	return {
		(vectorA.y * vectorB.z) - (vectorA.z * vectorB.y), // X
		-((vectorA.x * vectorB.z) - (vectorA.z * vectorB.x)), // Y
		(vectorA.x * vectorB.y) - (vectorA.y * vectorB.x)  // Z
	};
}

inline Vector3 GetProjection(const Vector3& vectorA, const Vector3& vectorB)
{
	float scalar = GetDotProduct(vectorA, vectorB) / (Square(GetMagnitude(vectorB)));
	return  vectorA - (vectorB * scalar);
}

inline Vector3 GetNormalVector(const Vector3& vector)
{
	const f32 magnitude = GetMagnitude(vector);

	return { vector.x / magnitude, vector.y / magnitude, vector.z / magnitude };
}

struct Vector2
{
	f32 x;
	f32 y;
};


inline Vector2 operator+(const Vector2& self, const Vector2& other)
{
	return {
		self.x + other.x, // X
		self.y + other.y, // Y
	};
}

inline Vector2 operator-(const Vector2& self, const Vector2& other)
{
	return {
		self.x - other.x, // X
		self.y - other.y, // Y
	};
}

inline Vector2 operator*(const Vector2& self, f32 scalar)
{
	return {
		self.x * scalar, // X
		self.y * scalar, // Y
	};
}

//get magnitude of current vector, also called norm or legth 
inline f32 GetMagnitude(const Vector2& vector)
{
	return sqrtf(Square(vector.x) + Square(vector.y));
}

inline f32 GetDotProduct(const Vector2& vectorA, const Vector2& vectorB)
{
	return (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y);
}

inline f32 GetAngle(const Vector2& vectorA, const Vector2& vectorB)
{
	f32 firstStepResult = GetDotProduct(vectorA, vectorB) / GetMagnitude(vectorA) * GetMagnitude(vectorB);
	return acosf(firstStepResult);
}

inline Vector2 GetCrossProduct(const Vector2& vectorA, const Vector2& vectorB)
{
	const Vector3 vectorAuxA = { vectorA.x, vectorA.y, 0.0f };
	const Vector3 vectorAuxB = { vectorB.x, vectorB.y, 0.0f };

	const Vector3 result = GetCrossProduct(vectorAuxA, vectorAuxB);

	return { result.x, result.y };
}

inline Vector2 GetProjection(const Vector2& vectorA, const Vector2& vectorB)
{
	float scalar = GetDotProduct(vectorA, vectorB) / (Square(GetMagnitude(vectorB)));
	return  vectorA - (vectorB * scalar);
}


inline Vector2 GetNormalVector(const Vector2& vector)
{
	const f32 magnitude = GetMagnitude(vector);

	return { vector.x / magnitude, vector.y / magnitude };
}

#endif //VECTOR_H
