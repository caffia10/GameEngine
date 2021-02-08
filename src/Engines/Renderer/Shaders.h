
#ifndef SHADERS_H
#define SHADERS_H

#include "OpenGL.h"
#include "Maths/MathDef.h"
#include "Common.h"


inline GLuint CreateShader(GLenum shaderType, std::string const  source, char const*  shaderName)
{
	i32 compileResult = 0;

	GLuint shader = glCreateShader(shaderType);

	i32 const shaderCodeSize =  (i32) source.size();

	 char const* sourcePtr = source.c_str();

	glShaderSource(shader, 1, &sourcePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_FALSE)
	{
		i32 infoLogLenght = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLenght);
		
		char* shaderLog = new char[infoLogLenght];
		glGetShaderInfoLog(shader, infoLogLenght, NULL, shaderLog);

		LOG("ERROR compiling shader: %s %s", shaderName, shaderLog);

		delete shaderLog;

		return 0;
	}

	return shader;
}

inline GLuint CreateShaderProgram(char const*  vertexShaderFilename, char const*  fragmentShaderFilename)
{
	std::string const  vertexShaderCode = ReadFile(vertexShaderFilename);

	std::string const  fragmentShaderCode = ReadFile(fragmentShaderFilename);

	GLuint const vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, "Vertex Shader");

	GLuint const fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "Fragment Shader");

	i32 linkResult = 0;

	// create the program handle, attach the shaders and link it
	GLuint const program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

	// check for link errors
	if (linkResult == GL_FALSE)
	{
		int infoLogLenght = 0;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLenght);

		char* logInfo = new char[infoLogLenght];

		glGetProgramInfoLog(program, infoLogLenght, NULL, logInfo);

		LOG("Shader load - LINK ERROR: %s", logInfo);

		delete logInfo;

		return 0;
	}

	return program;
}


#endif  // SHADERS_H


