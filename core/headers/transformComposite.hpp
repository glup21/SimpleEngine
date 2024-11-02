#ifndef TRANSFORM_COMPOSITE_HPP
#define TRANSFORM_COMPOSITE_HPP

#include <vector>
//#include "transform.hpp"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


using std::vector, glm::mat4, glm::vec3, glm::vec4;

class TransformComposite
{
private:
    vector<TransformComposite*> transforms;
    mat4 combinedMatrix;

public:
    TransformComposite() = default;
    virtual mat4 getTransformMatrix();
    void addTransform(TransformComposite* transform);

};

#endif
