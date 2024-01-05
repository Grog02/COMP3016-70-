#ifndef VAO_CLASS_H
#define  VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	// ID of the Vertex Array Object
	GLuint ID;
	VAO();
	// links VBO to VAO
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// binds, unbinds and deletes VAO 
	void Bind();
	void Unbind();
	void Delete();
};
#endif