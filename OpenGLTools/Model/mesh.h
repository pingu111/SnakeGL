#ifndef MESH_H
#define MESH_H

#include <vector>
#include <assimp/mesh.h>
#include <GL/glew.h>
#include "../glm.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

struct Mesh
{
    Mesh(aiMesh const *mesh);

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    unsigned materialIndex;
};

#endif // MESH_H
