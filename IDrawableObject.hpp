#ifndef IDRAWABLEOBJECT_H
#define IDRAWABLEOBJECT_H
#include "shader.hpp"
class IDrawableObject
{
public:
    virtual ~IDrawableObject() = 0;
    virtual void draw(Shader* shader = nullptr) = 0;
    virtual void setup(Shader* shader = nullptr) = 0;
};
inline IDrawableObject::~IDrawableObject() {}
#endif