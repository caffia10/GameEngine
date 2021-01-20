
#ifndef OPENGL_RENDER_B
#define OPENGL_RENDER_B

#include <windows.h>
#include "Engines/Maths/Calcs.h"
#include "OpenGL.h"
#include "Common.h"
#include <vector>
#include "Camera.h"
#include "Mesh.h"
#include "Mesh.cpp"
#include "Shaders.h"
#include "TextureLoader.cpp"

static Camera camera;
static MeshRender** meshRenderers;

void ClearBuffers(f32 red, f32 green, f32 blue, f32 alpha)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(red, green, blue, alpha);
}

void InitializeScene()
{
	// Enable the depth testing
	glEnable(GL_DEPTH_TEST);

	f32 const FOV = 45.0f;
	f32 const width = 1024;
	f32 const heigth = 768;
	f32 const nearPlane = 0.1f;
	f32 const farPlane = 100.0f;
	Vector3 const position = Vector3{ 0.0f, 4.0f, 4.0f };
	Matrix4 const projectionMatrix = CreateProjectionMatrix(FOV, width, heigth, nearPlane, farPlane);
	Matrix4 const viewMatrix = CreateViewMatrix(position);

	camera = {
		FOV,
		width,
		heigth,
		nearPlane,
		farPlane,
		position,
		projectionMatrix,
		viewMatrix
	};

	Mesh *sphereMesh = new Mesh();

	SetSphereData(sphereMesh);
	sphereMesh->position = Vector3(0.0f);
	sphereMesh->scale = Vector3(1.0f);

	sphereMesh->program = CreateShaderProgram(
		"data/Assets/Shaders/TexturedModel.vs",
		"data/Assets/Shaders/TexturedModel.fs"
	);
	
	sphereMesh->texture = GetTextureID("data/Assets/Textures/globe.jpg");
	
	MeshRender* sphereRender = CreateMeshRender(sphereMesh);

	meshRenderers = (MeshRender**) malloc(1 * sizeof(MeshRender*));
	meshRenderers[0] = sphereRender;
}

void RenderScene()
{
	ClearBuffers(1.0f, 1.0f, 0.0f, 1.0f);

	// Draw game objects her
	for (size_t i = 0; i < 1; i++)
	{
		DrawMesh(*(meshRenderers + i), &camera);
	}
	
}

void ReleaseRender()
{
	for (size_t i = 0; i < 1; i++)
	{
		delete &meshRenderers[i];
	}
}

#endif // OPENGL_RENDER_B