#ifndef IDRAWABLEOBJECT_H
#define IDRAWABLEOBJECT_H

class IDrawableObject
{
public:
    virtual ~IDrawableObject() = 0;
    virtual void draw() = 0;
    virtual void setup() = 0;
};
inline IDrawableObject::~IDrawableObject() {}
#endif