#include "VAO.h"
// Vertex Array Object 
VAO::VAO()
{
	// Generate new VAO  
	glGenVertexArrays(1, &ID);
}
// Linkss a Vertex Buffer Array to the VAO
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	// Binds VBO
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}
// Binds VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}
// Unbinds VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}
// Deletes VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}