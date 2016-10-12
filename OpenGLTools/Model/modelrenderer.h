#ifndef MODELRENDERER_H
#define MODELRENDERER_H

#include "modelimporter.h"

class ModelRenderer
{
public:
    ModelRenderer(std::string const &path, TextureRepository &textureRepository);

    void draw(bool takeCareAboutMaterials, GLint colorLocation = 0, GLint useTextureLocation = 0);

    ~ModelRenderer();

private:
    ModelImporter mModelImporter;
   std::vector<GLuint> mVaos;
   std::vector<GLuint> mVbos;
   std::vector<GLuint> mIbos;

    void configureVbo();
    void configureIbo();
    void configureVao();
};

#endif // MODELRENDERER_H
