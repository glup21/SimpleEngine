#ifndef BASEIMAGE_H
#define BASEIMAGE_H

#include <string>
#include <vector>

using std::vector, std::string;

class BaseImage
{
public:
    ~BaseImage() = default;

    bool load(const string& filePath);

    int getWidth();
    int getHeight();
    const vector<unsigned char>& getPixelData();
    void setPixelData(const std::vector<unsigned char>& pixelData);

protected:
    int width;
    int height;
    int nrChannels;
    vector<unsigned char> pixelData;
};

#endif 