#ifndef QUATERNIONS_H
#define QUATERNIONS_H

#include "MathDef.h"

struct Quaternion
{
	f32 x;
	f32 y;
	f32 z;
	f32 w;

};

inline Quaternion operator*(const Quaternion& self, const Quaternion& other)
{
	Quaternion result;

	result.w = self.w * other.w - self.x * other.x - self.y * other.y - self.z * other.z;
	result.x = self.w * other.x + self.x * other.w + self.y * other.z - self.z * other.y;
	result.y = self.w * other.y - self.x * other.z + self.y * other.w + self.z * other.x;
	result.z = self.w * other.z + self.x * other.y - self.y * other.x + self.z * other.w;

	return result;
}

inline Quaternion operator*(const Quaternion& self, const f32 scalar)
{
	Quaternion result;

	result.w = self.w * scalar;
	result.x = self.x * scalar;
	result.y = self.y * scalar;
	result.z = self.z * scalar;

	return result;
}

inline Quaternion operator/(const Quaternion& self, const f32 scalar)
{
	Quaternion result;

	result.w = self.w / scalar;
	result.x = self.x / scalar;
	result.y = self.y / scalar;
	result.z = self.z / scalar;

	return result;
}

inline Quaternion operator+(const Quaternion& self, const Quaternion& other)
{
	Quaternion result;

	result.w = self.w + other.w;
	result.x = self.x + other.x;
	result.y = self.y + other.y;
	result.z = self.z + other.z;

	return result;
}

inline f32 GetMagnitude(const Quaternion& quaternion)
{
	return sqrtf(Square(quaternion.w) + Square(quaternion.x) + Square(quaternion.y) + Square(quaternion.z));
}

inline Quaternion GetConjugate(const Quaternion& quaternion)
{
	return { -quaternion.x, -quaternion.y, -quaternion.z, quaternion.w };
}

inline Quaternion GetInverse(const Quaternion& quaternion)
{
	return  GetConjugate(quaternion) / GetMagnitude(quaternion);
}

inline Quaternion GetUnitQuaternion(const Quaternion& quaternion)
{
	return quaternion / GetMagnitude(quaternion);
}

#endif