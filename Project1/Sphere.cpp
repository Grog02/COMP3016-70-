#include "sphere.h"
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Sphere::Sphere() : VAO(0), VBO(0), EBO(0), radius(1.0f), latitudeLines(20), longitudeLines(20), isInitialized(false) {}

Sphere::Sphere(float radius, unsigned int latitudeLines, unsigned int longitudeLines)
    : radius(radius), latitudeLines(latitudeLines), longitudeLines(longitudeLines), VAO(0), VBO(0), EBO(0), isInitialized(false) {}

void Sphere::SetBuffers(unsigned int vao, unsigned int vbo, unsigned int ebo) {
    VAO = vao;
    VBO = vbo;
    EBO = ebo;
}

void Sphere::Initialize() {
    if (isInitialized) return;

    generateSphere();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    isInitialized = true;
}

void Sphere::generateSphere() {
    vertices.clear();
    indices.clear();

    for (unsigned int y = 0; y <= latitudeLines; ++y) {
        for (unsigned int x = 0; x <= longitudeLines; ++x) {
            float xSegment = static_cast<float>(x) / longitudeLines;
            float ySegment = static_cast<float>(y) / latitudeLines;

            float xPos = radius * std::cos(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
            float yPos = radius * std::cos(ySegment * M_PI);
            float zPos = radius * std::sin(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);

            vertices.push_back(glm::vec3(xPos, yPos, zPos));
        }
    }

    for (unsigned int i = 0; i < latitudeLines; ++i) {
        for (unsigned int j = 0; j < longitudeLines; ++j) {
            indices.push_back(i * (longitudeLines + 1) + j);
            indices.push_back((i + 1) * (longitudeLines + 1) + j);
            indices.push_back(i * (longitudeLines + 1) + j + 1);

            indices.push_back(i * (longitudeLines + 1) + j + 1);
            indices.push_back((i + 1) * (longitudeLines + 1) + j);
            indices.push_back((i + 1) * (longitudeLines + 1) + j + 1);
        }
    }
}


void Sphere::Draw() {
    if (!isInitialized) return;

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
