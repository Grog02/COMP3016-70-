#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

// Function to read file contents
std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;
	// Builds shader from vertex and fragment shader files
	Shader(const char* vertexFile, const char* fragmentFile);
	// Activates/deletes shader
	void Activate();
	void Delete();
private:
	// Check for errors 
	void compileErrors(unsigned int shader, const char* type);
};

#endif