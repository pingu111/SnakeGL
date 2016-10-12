#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <vector>
#include "texture.h"

class Framebuffer : public GLResource
{
public:
    Framebuffer();

    void addColorRenderTarget(shared_ptr<Texture> const &colorBuffer);
    void changeDepthBuffer(shared_ptr<Texture> const &depthBuffer);

    GLuint nameColor(size_t i);
    GLuint nameDepth();

    ~Framebuffer();
private:
   std::vector<shared_ptr<Texture>> mColorBuffers;
    shared_ptr<Texture> mDepthBuffer;
};

#endif // FRAMEBUFFER_H
