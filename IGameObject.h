#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include "transform.h"

class IGameObject
{
protected:
    Transform transform;

public:
    //virtual ~IGameObject() = default;
    virtual void update() = 0;
    virtual Transform getTransform() = 0;
    virtual void setTransform(const Transform& transform) = 0;


};

#endif