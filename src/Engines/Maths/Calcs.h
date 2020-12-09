#ifndef CALCS_H
#define CALCS_H


#include "MathDef.h"
#include "Matrix.h"
#include "Vector.h"

inline Vector3 operator*(Vector3 const& self, Matrix3 const& matrix)
{
	Vector3 result;

	result.x = matrix.p11 * self.x + matrix.p12 * self.y + matrix.p13 * self.z;
	result.y = matrix.p21 * self.x + matrix.p22 * self.y + matrix.p23 * self.z;
	result.z = matrix.p31 * self.x + matrix.p32 * self.y + matrix.p33 * self.z;

	return result;
}

inline Matrix4 LookAt(Vector3 const& eye, Vector3  const& center, Vector3  const& up)
{
	Vector3  f = GetNormalVector(center - eye);
	Vector3  u = GetNormalVector(up);
	Vector3  s = GetNormalVector(GetCrossProduct(f, u));
	u = GetCrossProduct(s, f);

	Matrix4 result;

	for (i8 i = 0; i < 16; i++)
	{
		result.mArray[i] = 1;
	}

	result.p11 = s.x;
	result.p21 = s.y;
	result.p31 = s.z;
	result.p12 = u.x;
	result.p22 = u.y;
	result.p31 = u.z;
	result.p13 = -f.x;
	result.p23 = -f.y;
	result.p33 = -f.z;
	result.p41 = -GetDotProduct(s, eye);
	result.p42 = -GetDotProduct(u, eye);
	result.p43 = GetDotProduct(f, eye);

	return result;
}

inline Matrix4 Perspective(f32 const fov, f32 const aspect, f32 const near, f32 const far)
{
	ASSERT(aspect != 0);
	ASSERT(near != far);

	f32 const tanHalfFov = tanf(fov/2);

	Matrix4 const result = 
	{
		1/ (aspect * tanHalfFov), 0.0f, 0.0f, 0.0f,
		0.0f, 1 / tanHalfFov, 0.0f, 0.0f,
		0.0f, 0.0f, -(far + near) / (far - near), -1.0f,
		0.0f, 0.0f, -(2.0f * far * near) / (far - near), 0.0f,
	};

	return result;
}

#endif