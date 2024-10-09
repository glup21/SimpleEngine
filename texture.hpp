#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "baseImage.hpp"

class Texture : public BaseImage
{
public:
    Texture() = default;
    Texture(string type);
    ~Texture();

    bool loadFromFile(const std::string& filePath);
    void bind(unsigned int unit = 0) const;
    void unbind() const;

    unsigned int getID() const;
    string getType() const;
private:
    unsigned int textureID;
    string type;
};

#endif // TEXTURE_H