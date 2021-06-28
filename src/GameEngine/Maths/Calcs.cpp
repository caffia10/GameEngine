#ifndef CALCS_B
#define CALCS_B

#include "MathDef.h"
#include "Matrix.cpp"
#include "Vector.cpp"
#include "Common/Common.h"

inline Vector3 operator*(Vector3 const& self, Matrix3 const& matrix)
{
	Vector3 result;

	result.x = matrix.p11 * self.x + matrix.p12 * self.y + matrix.p13 * self.z;
	result.y = matrix.p21 * self.x + matrix.p22 * self.y + matrix.p23 * self.z;
	result.z = matrix.p31 * self.x + matrix.p32 * self.y + matrix.p33 * self.z;

	return result;
}

Matrix4 LookAt(Vector3 const& eye, Vector3  const& center, Vector3  const& up)
{
	Vector3 const  f = GetNormalVector(center - eye);
	Vector3 const  s = GetNormalVector(GetCrossProduct(f, up));
	Vector3 const  u = GetCrossProduct(s, f);

	Matrix4 result = Matrix4(1.0f);

	result.p11 = s.x;
	result.p21 = s.y;
	result.p31 = s.z;

	result.p12 = u.x;
	result.p22 = u.y;
	result.p32 = u.z;
	
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


inline Matrix4 Translate(Matrix4 const matrix, Vector3 vector)
{
	Matrix4 result(matrix);

	result.p41 = matrix.p11 * vector.x + matrix.p21 * vector.y + matrix.p31 * vector.z + matrix.p41;
	result.p42 = matrix.p12 * vector.x + matrix.p22 * vector.y + matrix.p32 * vector.z + matrix.p42;
	result.p43 = matrix.p13 * vector.x + matrix.p23 * vector.y + matrix.p33 * vector.z + matrix.p43;
	result.p44 = matrix.p14 * vector.x + matrix.p24 * vector.y + matrix.p34 * vector.z + matrix.p44;
	
	return result;
}

inline Matrix4 Scale(Matrix4 const matrix, Vector3 const scalar)
{
	Matrix4 const ScalingMatrix = {
		scalar.x, 0.0f, 0.0f, 0.0f,
		0.0f, scalar.y, 0.0f, 0.0f,
		0.0f, 0.0f, scalar.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};

	return matrix * ScalingMatrix;
}

#endif // CALCS_B