#include "transformComposite.hpp"

mat4 TransformComposite::getTransformMatrix() 
{
    combinedMatrix = mat4(1.0f); 
    for (TransformComposite* transform : transforms) 
    {
        combinedMatrix *= transform->getTransformMatrix(); 
    }
    return combinedMatrix; 
}

void TransformComposite::addTransform(TransformComposite* transform) 
{
    transforms.push_back(transform);
}
