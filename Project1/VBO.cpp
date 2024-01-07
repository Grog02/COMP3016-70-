#include "VBO.h"
// Vertex Buffer Array with vector of vertices
VBO::VBO(std::vector<Vertex>& vertices)
{
	// Generate new VBO and binds it 
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}
// VBO with array of vertices
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	// Generate new VBO and binds it
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Binds VBO
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
// Unbinds VBO
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
// Deletes VBO
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}