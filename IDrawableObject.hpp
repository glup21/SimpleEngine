#ifndef IDRAWABLEOBJECT_H
#define IDRAWABLEOBJECT_H
#include "shader.hpp"
#include "shaderProgram.hpp"
class IDrawableObject
{
protected:
    ShaderProgram* shaderProgram;
public: 
    IDrawableObject(ShaderProgram* shaderProgram) : shaderProgram(shaderProgram) {}
    virtual void draw() = 0;
    virtual void setup() = 0;
};

#endif