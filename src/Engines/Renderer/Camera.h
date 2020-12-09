
#ifndef CAMERA_H
#define CAMERA_H

#include "Engines/Maths/Calcs.h"


inline Matrix4 CreateViewMatrix(Vector3 cameraPos)
{
	const Vector3 cameraFront = Vector3{ 0.0f, 0.0f, 0.0f };
	const Vector3 cameraUp = Vector3{ 0.0f, 1.0f, 0.0f };

	return LookAt(cameraPos, cameraFront, cameraUp);
}

inline Matrix4 CreateProjectionMatrix(f32 const fov, f32 const width, f32 height, f32 const nearPlane, f32 const farPlane)
{
	f32 const aspect = width / height;

	return Perspective(fov, aspect, nearPlane, farPlane);
}
#endif // CAMERA_H