#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Sphere {
public:
    Sphere();
    Sphere(float radius, unsigned int latitudeLines, unsigned int longitudeLines);
    void SetBuffers(unsigned int vao, unsigned int vbo, unsigned int ebo);
    void Initialize();
    void Draw();

private:
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> indices;
    unsigned int VAO, VBO, EBO;
    float radius;
    unsigned int latitudeLines, longitudeLines;
    bool isInitialized;

    void generateSphere();
};

#endif // SPHERE_H
