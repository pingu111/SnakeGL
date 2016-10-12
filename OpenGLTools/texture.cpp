#include <algorithm>
#include "texture.h"

Texture::Texture()
{
    glGenTextures(1, &mId);
}

unique_ptr<Texture> Texture::loadImage2D(const std::string &path) {
    unique_ptr<Texture> texture =std::make_unique<Texture>();

    SDL_Surface *surface = IMG_Load(path.c_str());

    if(surface == nullptr)
        throw runtime_error(path + " does not opened");

    GLenum format, internalFormat;

    getFormats(surface, internalFormat, format);

    GLsizei numMipmaps = ((GLsizei)log2(max(surface->w, surface->h)) + 1);

    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexStorage2D(GL_TEXTURE_2D, numMipmaps, internalFormat, surface->w, surface->h);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, surface->w, surface->h,
                        format, GL_UNSIGNED_BYTE, surface->pixels);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(surface);

    return texture;
}

shared_ptr<Texture> Texture::texture2D(GLuint w, GLuint h, GLenum internalFormat) {
    auto rt = make_shared<Texture>();

    glBindTexture(GL_TEXTURE_2D, *rt);

    glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, w, h);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    return rt;
}

void Texture::getFormats(SDL_Surface *img, GLenum &internalFormat, GLenum &format) {
    if(img->format->BytesPerPixel == 3) {
        internalFormat = GL_RGB8;

        if(img->format->Rmask == 0x000000FF)
            format = GL_RGB;

        else
            format = GL_BGR;
    }

    else {
        internalFormat = GL_RGBA8;

        if(img->format->Rmask == 0x000000FF)
            format = GL_RGBA;

        else
            format = GL_BGRA;
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &mId);
}
