#ifndef IDRAWABLEOBJECT_H
#define IDRAWABLEOBJECT_H
#include "shader.hpp"
#include "shaderProgram.hpp"
class IDrawableObject
{
protected:
    ShaderProgram* shaderProgram;
    int ID;
public: 
    IDrawableObject(ShaderProgram* shaderProgram, int ID) : shaderProgram(shaderProgram), ID(ID) {}
    virtual void draw() = 0;
    virtual void setup() = 0;
};

#endif