
#ifndef CAMERA_H
#define CAMERA_H

#include "Maths/Calcs.cpp"

struct Camera
{
	f32 FOV;
	i32 width;
	i32 heigth;
	f32 nearPlane;
	f32 farPlane;
	Vector3 position;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
};

inline Matrix4 CreateViewMatrix(Vector3 cameraPos)
{
	const Vector3 cameraFront = Vector3{ 0.0f, 0.0f, 0.0f };
	const Vector3 cameraUp = Vector3{ 0.0f, 1.0f, 0.0f };

	return LookAt(cameraPos, cameraFront, cameraUp);
}

inline Matrix4 CreateProjectionMatrix(
	f32 const fov,
	i32 const width,
	i32 const height,
	f32 const nearPlane,
	f32 const farPlane)
{
	i32 const aspect = width / height;

	return Perspective(fov, static_cast<f32>(aspect), nearPlane, farPlane);
}
#endif // CAMERA_H