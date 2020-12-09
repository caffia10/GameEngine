
#ifndef OPENGL_RENDER_B
#define OPENGL_RENDER_B

#include <windows.h>
#include "Engines/Maths/Vector.h"
#include "OpenGL.h"
#include "Common.h"
#include <vector>
#include "Camera.h"

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector3 color;

};

GLuint program;
GLuint VAO;
GLuint VBO;
GLuint EBO;
Matrix4 projectionMatrix, viewMatrix;
const std::vector<GLuint> indices = {0, 1, 2,};

void ClearBuffers(f32 red, f32 green, f32 blue, f32 alpha)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(red, green, blue, alpha);
}



void InitializeScene()
{
	glEnable(GL_DEPTH_TEST);

	const std::vector<Vertex> vertices = {
		{ { 0.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 1.0f, 0.0f, 0.0 } },
		{ { 1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 0.0f, 1.0f, 0.0 } },
		{ { -1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 0.0f, 0.0f, 1.0 } },
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(Vertex)  * vertices.size(),
		&vertices[0],
		GL_STATIC_DRAW);

	//Attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(offsetof(Vertex, Vertex::color))
	);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	const Vector3 cameraPos = Vector3{ 0.0f, 4.0f, 6.0f };
	viewMatrix = CreateViewMatrix(cameraPos);
	projectionMatrix = CreateProjectionMatrix();
}

void RenderScene()
{
	ClearBuffers(1.0f, 1.0f, 0.0f, 1.0f);

	// Draw game objects her

	Matrix4 model;

	glUseProgram(program);

	GLint modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.mArray);

	GLint vLoc = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(vLoc, 1, GL_FALSE, viewMatrix.mArray);


	GLint pLoc = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, projectionMatrix.mArray);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);

}



#endif // OPENGL_RENDER_B