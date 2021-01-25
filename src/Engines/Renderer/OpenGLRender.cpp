
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
static u32 frameBuffer;

void ClearBuffers(f32 red, f32 green, f32 blue, f32 alpha)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(red, green, blue, alpha);
}

void InitializeScene(f32 const cameraWidth, f32 const cameraHeight)
{
	

	f32 const FOV = 45.0f;
	f32 const nearPlane = 0.1f;
	f32 const farPlane = 100.0f;
	Vector3 const position = Vector3{ 0.0f, 4.0f, 4.0f };
	Matrix4 const projectionMatrix = CreateProjectionMatrix(FOV, cameraWidth, cameraHeight, nearPlane, farPlane);
	Matrix4 const viewMatrix = CreateViewMatrix(position);

	camera = {
		FOV,
		cameraWidth,
		cameraHeight,
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

	glGenFramebuffers(1, &frameBuffer);
	glBindBuffer(GL_FRAMEBUFFER, frameBuffer);

	sphereMesh->program = CreateShaderProgram(
		"data/Assets/Shaders/TexturedModel.vs",
		"data/Assets/Shaders/TexturedModel.fs"
	);
	
	sphereMesh->texture = GetTextureID("data/Assets/Textures/globe.jpg");

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sphereMesh->texture, 0);

	u32 depthRendeBuffer;
	glGenRenderbuffers(1, &depthRendeBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthRendeBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRendeBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
	

	MeshRender* sphereRender = CreateMeshRender(sphereMesh);

	 //glBindFramebuffer(GL_FRAMEBUFFER, 0);

	meshRenderers = (MeshRender**) malloc(1 * sizeof(MeshRender*));
	meshRenderers[0] = sphereRender;
}

void RenderScene()
{
	glBindBuffer(GL_FRAMEBUFFER, frameBuffer);

	ClearBuffers(0.0f, 0.0f, 0.0f, 1.0f);
	// Enable the depth testing
	glEnable(GL_DEPTH_TEST);
	
	// Draw game objects her
	for (size_t i = 0; i < 1; i++)
	{
		DrawMesh(*(meshRenderers + i), &camera);
	}

	glDisable(GL_DEPTH_TEST);
	glBindBuffer(GL_FRAMEBUFFER, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6); 
	
}

void ReleaseRender()
{
	for (size_t i = 0; i < 1; i++)
	{
		delete &meshRenderers[i];
	}
}

void ChangeViewPort(f32 const width, f32 const height)
{
	 glViewport(0, 0, width, height);
}

#endif // OPENGL_RENDER_B