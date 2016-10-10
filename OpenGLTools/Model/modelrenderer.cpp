#include "modelrenderer.h"

ModelRenderer::ModelRenderer(const std::string &path, TextureRepository &textureRepository) :
    mModelImporter(path, textureRepository),
    mVaos(mModelImporter.meshes.size(), 0),
    mVbos(mModelImporter.meshes.size(), 0),
    mIbos(mModelImporter.meshes.size(), 0) {
    configureVbo();
    configureIbo();
    configureVao();
}

void ModelRenderer::draw(bool takeCareAboutMaterials, GLint colorLocation, GLint useTextureLocation) {
    for(int i = 0; i < mVaos.size(); ++i) {
        glBindVertexArray(mVaos[i]);

        if(takeCareAboutMaterials) {
            if(mModelImporter.materials[mModelImporter.meshes[i].materialIndex].useTexture) {
                glUniform1i(useTextureLocation, 1);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, mModelImporter.materials[mModelImporter.meshes[i].materialIndex].texture);
            }

            else {
                auto color = mModelImporter.materials[mModelImporter.meshes[i].materialIndex].color;
                glUniform1i(useTextureLocation, 0);
                glUniform3f(colorLocation, color.r, color.g, color.b);
            }
        }

        glDrawElements(GL_TRIANGLES, mModelImporter.meshes[i].indices.size(), GL_UNSIGNED_INT, 0);
    }
}

void ModelRenderer::configureVbo() {
    glGenBuffers(mVbos.size(), &mVbos[0]);

    for(int i = 0; i < mVbos.size(); ++i) {
        glBindBuffer(GL_ARRAY_BUFFER, mVbos[i]);
        glBufferData(GL_ARRAY_BUFFER, mModelImporter.meshes[i].vertices.size() * sizeof(Vertex), &mModelImporter.meshes[i].vertices[0], GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelRenderer::configureIbo() {
    glGenBuffers(mIbos.size(), &mIbos[0]);

    for(int i = 0; i < mIbos.size(); ++i) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbos[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mModelImporter.meshes[i].indices.size() * sizeof(GLuint), &mModelImporter.meshes[i].indices[0], GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ModelRenderer::configureVao() {
    glGenVertexArrays(mVaos.size(), &mVaos[0]);

    for(int i = 0; i < mVaos.size(); ++i) {
        glBindVertexArray(mVaos[i]);
        glBindBuffer(GL_ARRAY_BUFFER, mVbos[i]);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (char*)0 + sizeof(glm::vec3));
        glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (char*)0 + sizeof(glm::vec3) * 2);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbos[i]);
    }

    glBindVertexArray(0);
}

ModelRenderer::~ModelRenderer() {
    for(auto &vao : mVaos)
        glDeleteVertexArrays(1, &vao);

    for(auto &ibo : mIbos)
        glDeleteBuffers(1, &ibo);

    for(auto &vbo : mVbos)
        glDeleteBuffers(1, &vbo);
}
