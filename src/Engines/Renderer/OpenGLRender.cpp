
#ifndef OPENGL_RENDER_B
#define OPENGL_RENDER_B

#include <windows.h>
#include "Maths/Calcs.cpp"
#include "OpenGL.h"
#include "Common/Common.h"
#include <vector>
#include "Camera.h"
#include "Mesh.h"
#include "Mesh.cpp"
#include "Shaders.h"
#include "Texture.cpp"


struct RendererJob
{
	u32 VAO;
	u32 VBO;
	u32 EBO;
	Mesh mesh;
	Texture texture;
	u32 shaderProgram;
};

static Camera mainCamera;
static RendererJob* rendererJobs;
static u32 frameBuffer;
static u32 renderedTexture;


void ClearBuffers(f32 red, f32 green, f32 blue, f32 alpha)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(red, green, blue, alpha);
}

void LoadMesh(RendererJob* render)
{
	glGenVertexArrays(1, &render->VAO);
	glBindVertexArray(render->VAO);

	glGenBuffers(1, &render->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, render->VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(Vertex) * render->mesh.vertexCount,
		&render->mesh.vertices[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &render->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render->EBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(u32) * render->mesh.indexCount,
		&render->mesh.indices[0],
		GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(GLvoid*)(offsetof(Vertex, Vertex::texCoords)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void InitializeFrameBuffer(i32 const& gameWidth, i32 const& gameHeight)
{
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	// craate frame buffer texture attachment
	glGenTextures(1, &renderedTexture);
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, gameWidth, gameHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, renderedTexture, 0);
	glBindTexture(GL_TEXTURE_2D,GL_TEXTURE_2D);

	// create renderbuffer 
	GLuint renderbuffer;
	glGenRenderbuffers(1, &renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,gameWidth, gameHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		THROWDEBUGBREAK;
	}

	glBindBuffer(GL_FRAMEBUFFER, 0);
}


void InitializeScene(i32 const& gameWidth, i32 const& gameHeight)
{
	f32 const FOV = 45.0f;
	f32 const nearPlane = 0.1f;
	f32 const farPlane = 100.0f;
	Vector3 const position = Vector3{ 0.0f, 4.0f, 4.0f };
	Matrix4 const projectionMatrix = CreateProjectionMatrix(FOV, gameWidth, gameHeight, nearPlane, farPlane);
	Matrix4 const viewMatrix = CreateViewMatrix(position);

	mainCamera = {
		FOV,
		gameWidth,
		gameHeight,
		nearPlane,
		farPlane,
		position,
		projectionMatrix,
		viewMatrix
	};

	RendererJob render = {};

	InitializeFrameBuffer(gameWidth, gameHeight);

	CreateSphereMesh(&render.mesh);

	render.shaderProgram = CreateShaderProgram(
		"data/Assets/Shaders/TexturedModel.vs",
		"data/Assets/Shaders/TexturedModel.fs"
	);

	LoadTexture(&render.texture,"data/Assets/Textures/globe.jpg");

	LoadMesh(&render);
	rendererJobs = (RendererJob*)malloc(1 * sizeof(RendererJob));
	rendererJobs[0] = render;
}

void Draw(RendererJob const* render, Camera const* camera)
{

	Matrix4 const translationMatrix = Translate(Matrix4(1.0f), render->mesh.position);

	Matrix4 const scaleMatrix = Scale(Matrix4(1.0f), render->mesh.scale);

	Matrix4 const modelMatrix = translationMatrix * scaleMatrix;

	Matrix4 const viewProjection = camera->viewMatrix * camera->projectionMatrix;

	glUseProgram(render->shaderProgram);

	GLint vpLoc = glGetUniformLocation(render->shaderProgram, "vp");
	glUniformMatrix4fv(vpLoc, 1, GL_FALSE, viewProjection.mArray);

	GLint modelLoc = glGetUniformLocation(render->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelMatrix.mArray);

	// Set Texture
	glBindTexture(GL_TEXTURE_2D, render->texture.id);

	glBindVertexArray(render->VAO);

	glDrawElements(GL_TRIANGLES, (GLsizei)render->mesh.indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}


void RenderScene()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	ClearBuffers(0.0f, 0.0f, 0.0f, 1.0f);
	// Enable the depth testing
	//glEnable(GL_DEPTH_TEST);

	// Draw game objects her
	for (size_t i = 0; i < 1; i++)
	{
		Draw((rendererJobs + i), &mainCamera);
	}

	//glDisable(GL_DEPTH_TEST);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void ReleaseRender()
{
	for (size_t i = 0; i < 1; i++)
	{
		delete &rendererJobs[i];
	}
}

void ChangeViewPort(i32 const width, i32 const height)
{
	glViewport(0, 0, width, height);
}

#endif // OPENGL_RENDER_B