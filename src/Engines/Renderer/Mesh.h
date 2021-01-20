#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Engines/Maths/Calcs.h"
#include "OpenGL.h"
#include "Common.h"
#include "Camera.h"

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
	u32 program;
	u32 texture;
};

struct MeshRender
{
	u32 VAO;
	u32 VBO;
	u32 EBO;
	Mesh* mesh;
};
#endif // MESH_H