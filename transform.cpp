#include "transform.hpp"

// Default constructor initializes the transformation matrix and other attributes
Transform::Transform() 
    : transformMatrix(mat4(1.0f)), 
      translationVec(vec3(0.0f)), 
      rotationVec(vec3(0.0f)), 
      rotationAngle(0.0), 
      scaleVec(vec3(1.0f)) {}

Transform::Transform(vec3 position, vec3 rotationAxis, float rotationAngle, vec3 scale) 
    : transformMatrix(mat4(1.0f)),
      translationVec(position), 
      rotationVec(rotationAxis), 
      rotationAngle(rotationAngle), 
      scaleVec(scale)
{
    transformMatrix = glm::translate(transformMatrix, position);
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotationAngle), rotationAxis);
    transformMatrix = glm::scale(transformMatrix, scale);
}

void Transform::rotate(float angle, float x, float y, float z) 
{
    mat4 rotationMatrix = glm::rotate(mat4(1.0f), glm::radians(angle), vec3(x, y, z));
    transformMatrix = rotationMatrix * transformMatrix; // Pre-multiply for correct order
    rotationVec = vec3(x, y, z); // Update rotation axis
    rotationAngle += angle; // Accumulate rotation angle if needed
}

void Transform::translate(float x, float y, float z) 
{
    mat4 translationMatrix = glm::translate(mat4(1.0f), vec3(x, y, z));
    transformMatrix = translationMatrix * transformMatrix; // Pre-multiply for correct order
    translationVec += vec3(x, y, z); // Accumulate translation
}

void Transform::scale(float x, float y, float z) 
{
    mat4 scalingMatrix = glm::scale(mat4(1.0f), vec3(x, y, z));
    transformMatrix = scalingMatrix * transformMatrix; // Pre-multiply for correct order
    scaleVec.x *= x; // Cumulative scaling in X
    scaleVec.y *= y; // Cumulative scaling in Y
    scaleVec.z *= z; // Cumulative scaling in Z
}

mat4 Transform::getTransformMatrix()
{
    return transformMatrix;
}

vec3 Transform::getTranslation()
{
    return translationVec;
}

vec3 Transform::getRotationVector()
{
    return rotationVec;
}

vec3 Transform::getScale()
{
    return scaleVec;
}

vec3 Transform::getPosition()
{
    return vec3(
        transformMatrix[3].x / transformMatrix[3].w,
        transformMatrix[3].y / transformMatrix[3].w,
        transformMatrix[3].z / transformMatrix[3].w
    );
}

double Transform::getRotationAngle()
{
    return rotationAngle;
}

mat4 TransformComposite::getTransformMatrix() 
{
    combinedMatrix = mat4(1.0f); 
    for (TransformComposite* t : transforms) {
        combinedMatrix *= t->getTransformMatrix(); 
    }
    return combinedMatrix; 
}

void Transform::reset() 
{
    transformMatrix = mat4(1.0f);
    translationVec = vec3(0.0f);
    rotationVec = vec3(0.0f);
    rotationAngle = 0.0;
    scaleVec = vec3(1.0f); 
}

void TransformComposite::addTransform(TransformComposite* transform) 
{
    transforms.push_back(transform);
}
