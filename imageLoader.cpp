#include "imageLoader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
u_char* ImageLoader::loadImage(const string& path, int* height, int* width, int* nrChannels)
{

    if (usedPath.find(path) != usedPath.end()) {
        std::cout << "Image already loaded: " << path << std::endl;
        return usedPath[path]; 
    }

    u_char* image = stbi_load(path.c_str(), width, height, nrChannels, 0);
    if (image) {
        std::cout << "Image loaded successfully: " << path << std::endl;
        usedPath[path] = image; 
    } else {
        std::cerr << "Failed to load image: " << path << std::endl;
    }
    return image;
}