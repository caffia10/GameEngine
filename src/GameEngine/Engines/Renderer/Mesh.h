#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Maths/Calcs.cpp"
#include "OpenGL.h"
#include "Common/Common.h"
#include "Camera.h"
#include "Texture.h"

enum MeshType 
{
	Triangle = 0,
	Quad = 1,
	Cube = 2,
	Sphere = 3
};

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector3 color;
	Vector2 texCoords;
};

struct Mesh
{
	u32 indexCount;
	GLuint *indices;
	u32 vertexCount;
	Vertex *vertices;
	Vector3 position;
	Vector3 scale;
};

#endif // MESH_H