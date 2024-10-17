#ifndef IDRAWABLEOBJECT_H
#define IDRAWABLEOBJECT_H
#include "shader.hpp"
#include "shaderProgram.hpp"
class IDrawableObject
{

    ShaderProgram* shaderProgram;
public:
    virtual void draw() = 0;
    virtual void setup() = 0;
};

#endif