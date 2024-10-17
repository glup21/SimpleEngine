#ifndef TRANSFORM_COMPOSITE_HPP
#define TRANSFORM_COMPOSITE_HPP

#include <vector>
#include "transform.hpp"

using std::vector;

class TransformComposite
{

    vector<TransformComposite*> transforms;
    glm::mat4 combined_matrix;



};

#endif