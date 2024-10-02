#ifndef TRANSFORM_H
#define TRANSFORM_H

struct Transform
{
    float position[3];
    float scale[3];
    float rotation[3];

    Transform()
    {
        position[0] = position[1] = position[2] = 0.0f;
        scale[0] = scale[1] = scale[2] = 1.0f;
        rotation[0] = rotation[1] = rotation[2] = 0.0f;
    }

};

#endif