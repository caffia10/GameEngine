#include <string>
#include "OpenGL.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "Engines/Maths/MathDef.h"

u32 GetTextureID(std::string texFileName)
{
	i32 width, height, channels;

	stbi_uc* image = stbi_load(
		texFileName.c_str(),
		&width,
		&height,
		&channels,
		STBI_rgb
	);

	u32 texture;
	// Load texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering
	//lTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Set mipmap quality
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, 
		GL_LINEAR_MIPMAP_LINEAR
	);
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,
		GL_LINEAR
	);

	// Create texture
	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		GL_RGB, 
		width, 
		height, 
		0, 
		GL_RGB, 
		GL_UNSIGNED_BYTE, 
		image);

	glGenerateMipmap(GL_TEXTURE_2D);

	// release data
	glBindTexture(GL_TEXTURE_2D,0);
	stbi_image_free(image);

	return texture;
}
