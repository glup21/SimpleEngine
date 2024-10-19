#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include "texture.hpp"
#include <vector>
#include <map>
#include <string>
using std::vector, std::map, std::pair, std::string;
class ImageLoader
{
private:
    map<string, u_char*> usedPath;

public:
    ImageLoader() = default;

    u_char* loadImage(const string& path, int* height, int* width, int* nrChannels);

};

#endif