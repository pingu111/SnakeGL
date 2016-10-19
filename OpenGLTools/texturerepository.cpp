#include "texturerepository.h"
#include <iostream>

GLuint TextureRepository::image2D(const std::string &path) {

	std::cout << "TextureRepository::image2D"<< path << std::endl;
    if(mTextures.find(path) == mTextures.end())
        mTextures.emplace(path, Texture::loadImage2D(path));
    return *mTextures[path];
}
