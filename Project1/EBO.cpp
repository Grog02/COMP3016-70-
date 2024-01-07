#include "EBO.h"
// Element Buffer Object
EBO::EBO(std::vector<GLuint>&  indices)
{
	// Generate new EBO and binds it 
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	// Introduce the vertices into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}
// EBO with array of indices
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	// Generate new VBO and binds it
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}
// Binds EBO
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
// Unbinds EBO
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
// Deletes EBO
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}