#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class EBO
{
public:
	// ID of the Element Buffer Object
	GLuint ID;
	// EBO with indices
	EBO(std::vector<GLuint>& indices);
	// initialise EBO with array of indices
	EBO(GLuint* indices, GLsizeiptr sizes);

	// binds, unbinds and deletes EBO 
	void Bind();
	void Unbind();
	void Delete();
};

#endif
