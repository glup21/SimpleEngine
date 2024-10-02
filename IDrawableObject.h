#ifndef IDRAWABLEOBJECT_H
#define IDRAWABLEOBJECT_H

#include "shaderProgram.h"

class IDrawableObject
{
public:
    virtual ~IDrawableObject() = 0;
    virtual void draw() = 0;
    //virtual void setup(){}; //So we can override only one setup function in derived class, not both
    virtual void setup(ShaderProgram* shaderProgram = nullptr){};
};
inline IDrawableObject::~IDrawableObject() {}
#endif