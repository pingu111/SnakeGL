#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H

#include <vector>

#include "mesh.h"
#include "material.h"


struct ModelImporter
{
	ModelImporter();
    ModelImporter(std::string const &path, TextureRepository &textureRepository);
    ~ModelImporter() = default;

    std::vector<Mesh> meshes;
    std::vector<Material> materials;
};

#endif // MODELIMPORTER_H
