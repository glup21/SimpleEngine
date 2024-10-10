#include "baseImage.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool BaseImage::load(const string& filePath)
{
    
    unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (imageData == nullptr) {
        return false;
    }

    //pixelData.assign(imageData, imageData + (width * height * nrChannels));
    stbi_image_free(imageData);
    return true;
}

int BaseImage::getWidth() 
{
    return width;
}

int BaseImage::getHeight() 
{
    return height;
}

const vector<unsigned char>& BaseImage::getPixelData() 
{
    return pixelData;
}

void BaseImage::setPixelData(const vector<unsigned char>& pixelData)
{
    this->pixelData = pixelData;
}