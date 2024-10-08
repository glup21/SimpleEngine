#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "baseImage.hpp"

class Texture : public BaseImage
{
public:
    Texture();
    ~Texture();

    bool loadFromFile(const std::string& filePath);
    void bind(unsigned int unit = 0) const;
    void unbind() const;

    unsigned int getID() const;

private:
    unsigned int textureID;
};

#endif // TEXTURE_H