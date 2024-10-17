#ifndef TRANSFORM_COMPOSITE_HPP
#define TRANSFORM_COMPOSITE_HPP

#include <vector>
#include "transform.hpp"

using std::vector;

class TransformComposite
{
private:
    vector<TransformComposite*> transforms;
    glm::mat4 combinedMatrix;

public:
    TransformComposite() = default;
    virtual glm::mat4 getTransformMatrix();
    void addTransform(TransformComposite* transform);

};

#endif
