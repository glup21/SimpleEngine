#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "imageLoader.hpp"
#include <string>
#include <vector>

using std::string;
class ImageLoader;

class Texture 
{
public:
    Texture() = default;
    Texture(const u_char* image, int width, int height, int nrChannels, string type);
    ~Texture();

    void bind(unsigned int unit = 0) const;
    void unbind() const;

    unsigned int getID() const;
    string getType() const;
private:
    unsigned int textureID;
    string type;
    int width;
    int height;
    int nrChannels;
};

#endif 