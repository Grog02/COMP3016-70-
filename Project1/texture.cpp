#include "texture.h"
// Loads and creates a texture
Texture::Texture(const char* image, const char* texType, GLuint slot)
{
	// Assign texture type
	type = texType;

	// Basic image properties 
	int widthImg, heightImg, numColCh;
	
	// flip image on load
	stbi_set_flip_vertically_on_load(true);

	// reads image from file 
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Error checking to see if image loads successfully
	if (bytes == nullptr)
	{
		std::cerr << "Failed to load texture: " << image << std::endl;
		image = NULL;
		
	}

	// Generates OpenGL texture
	glGenTextures(1, &ID);

	// assigns texture to texture unit
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	// configures algorithm to scale the image
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// configures the way the texture is shown
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	// Creates texture with the appropriate colour format
	if (numColCh == 4)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else if (numColCh == 3)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else if (numColCh == 1)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else
		throw std::invalid_argument("Automatic Texture type recognition failed");

	// generates mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	// deletes image data after being stored
	stbi_image_free(bytes);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);

	// activate shader before changing uniform
	shader.Activate();
	glUniform1i(texUni, unit);
}
// Binds texture
void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}
// Unbinds texture
void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
// Deletes texture
void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}