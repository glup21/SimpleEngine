#ifndef IDRAWABLEOBJECT_H
#define IDRAWABLEOBJECT_H
#include "shader.hpp"
#include "shaderProgram.hpp"
class IDrawableObject
{
protected:
    int ID;
public: 
    IDrawableObject(int ID) : ID(ID) {}
    virtual void draw() = 0;
    virtual void setup() = 0;
};

#endif