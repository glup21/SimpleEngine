#include "baseImage.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool BaseImage::load(const std::string& filePath)
{
    int channels;
    unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (imageData == nullptr) {
        return false;
    }

    pixelData.assign(imageData, imageData + (width * height * channels));
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

const std::vector<unsigned char>& BaseImage::getPixelData() 
{
    return pixelData;
}

void BaseImage::setPixelData(const std::vector<unsigned char>& pixelData)
{
    this->pixelData = pixelData;
}