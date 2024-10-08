#ifndef BASEIMAGE_H
#define BASEIMAGE_H

#include <string>
#include <vector>

class BaseImage
{
public:
    ~BaseImage() = default;

    bool load(const std::string& filePath);

    int getWidth();
    int getHeight();
    const std::vector<unsigned char>& getPixelData();
    void setPixelData(const std::vector<unsigned char>& pixelData);

protected:
    int width;
    int height;
    std::vector<unsigned char> pixelData;
};

#endif 