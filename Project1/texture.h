#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	// Type of texture
	const char* type;
	// Texture unit
	GLuint unit;
	// Create texture from image file
	Texture(const char* image, const char* texType, GLuint slot);

	// Assign texture unit to texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds/Unbinds/Deletes texture
	void Bind();
	void Unbind();
	void Delete();
};
#endif