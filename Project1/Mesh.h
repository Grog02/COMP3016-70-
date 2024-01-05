#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>

#include "VAO.h"
#include "EBO.H"
#include "Camera.h"
#include "texture.h"



class Mesh
{
public:
	// Store Vertices, Indices and Textures
	std::vector <Vertex> vertices; 
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	// Vertex Array Object 
	VAO VAO;

	// Initialise mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	// Draw mesh 
	void Draw
	(
		Shader& shader,
		Camera& camera,
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
};


#endif

