#ifndef MATERIAL_H
#define MATERIAL_H

#include <assimp/material.h>
#include "../glm.h"
#include "../texturerepository.h"
#include <GL/glew.h>
struct Material {
    Material(aiMaterial *mtl, TextureRepository &tr, std::string const &globalPath);

    glm::vec3 color;
    GLuint texture;
    bool useTexture = false;
};

#endif // MATERIAL_H
