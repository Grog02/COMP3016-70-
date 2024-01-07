#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<json/json.h>
#include"Mesh.h"

using json = nlohmann::json;


class Model
{
public:
	// Loads model from file
	Model(const char* file);
	
	// Draws model
	void Draw(Shader& shader, Camera& camera);

private:
	// Path to file
	const char* file;
	// Data of file
	std::vector<unsigned char> data;
	// JSON object
	json JSON;

	// Vectors for storing data of each of the nodes
	std::vector<Mesh> meshes;
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;

	// Texture loading management
	std::vector<std::string> loadedTextureName;
	std::vector<Texture> loadedTexture;

	// load a mesh by the index
	void loadMesh(unsigned int indexMesh);

	// Goes through each node with recursion
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	// Gets the binary data from a file
	std::vector<unsigned char> getData();
	// Interpret the binary data
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();

	// Assembles the vertices from the components
	std::vector<Vertex> assembleVertices
	(
		std::vector<glm::vec3> positions,
		std::vector<glm::vec3> normals,
		std::vector<glm::vec2> texUVs
	);

	// Group float data
	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};
#endif