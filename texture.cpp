#include "texture.hpp"
#include <iostream>
#include <GL/glew.h>
#include <cstring>

Texture::Texture(const u_char* image, int width, int height, int nrChannels, std::string type)
    : width(width), height(height), nrChannels(nrChannels), type(type)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format;
    if (nrChannels == 1) {
        format = GL_RED; 
    } else if (nrChannels == 3) {
        format = GL_RGB; 
    } else if (nrChannels == 4) {
        format = GL_RGBA; 
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}



Texture::~Texture()
{
    //Somewhere in code texture desctructor is called before render, and I dont know where...
    //glDeleteTextures(1, &textureID);
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