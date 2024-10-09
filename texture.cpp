#include "texture.hpp"
#include <iostream>
#include <GL/glew.h>

Texture::Texture(string type) : textureID(0), type(type)
{
    glGenTextures(1, &textureID);
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}

bool Texture::loadFromFile(const std::string& filePath)
{
    if (!load(filePath)) { 
        std::cerr << "Failed to load texture: " << filePath << std::endl;
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getWidth(), getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, getPixelData().data());
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

void Texture::bind(unsigned int unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getID() const
{
    return textureID;
}

string Texture::getType() const
{
    return type;
}