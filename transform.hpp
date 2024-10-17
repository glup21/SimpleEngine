#define X_AXIS {1.0f, 0.0f, 0.0f}
#define Y_AXIS {0.0f, 1.0f, 0.0f}
#define Z_AXIS {0.0f, 0.0f, 1.0f}

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include "transformComposite.hpp"
using glm::vec3, glm::vec4, glm::mat4, glm::quat;



class Transform : public TransformComposite
{
private:
    mat4 transformMatrix;
    vec3 translationVec= vec3(0.0f);
    vec3 rotationVec = vec3(0.0f);
	double rotationAngle = 0.0f;
	vec3 scaleVec = vec3(0.0f);

public:
    Transform();
    Transform(vec3 position, vec3 rotationAxis, float rotationAngle, vec3 scale);
    void rotate(float angle, float x, float y, float z);
	void translate(float x, float y, float z);
	void scale(float x, float y, float z);

    mat4 getTransformMatrix() override;
    vec3 getTranslation();
    vec3 getRotationVector();
    vec3 getScale();

    vec3 getPosition();
    double getRotationAngle();

    void reset();
    
};

#endif