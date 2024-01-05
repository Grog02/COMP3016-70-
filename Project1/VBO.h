#ifndef VBO_CLASS_H
#define  VBO_CLASS_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

// structure for vertex used in mesh
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 colour;
	glm::vec2 texUV;
};

class VBO
{
public:
	GLuint ID;
	VBO(std::vector<Vertex>& vertices);
	VBO(GLfloat* vertices, GLsizeiptr size);


	void Bind();
	void Unbind();
	void Delete();
};

#endif