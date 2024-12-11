#ifndef CAMERA_H
#define CAMERA_H

#include "shaderProgram.hpp"
#include "cameraSettings.hpp"
#include "transformComposite.hpp"
#include "subject.hpp"
#include <GLFW/glfw3.h>
#include "SpotLight.hpp"
using glm::vec3, glm::mat4;

class ShaderProgram;
class SpotLight;

class Camera : public Subject {
private:
    TransformComposite transform; 
    vec3 target;
    vec3 upVector;
    GLFWwindow* window;
    CameraSettings settings;
    float ratio;


public:
    Camera(GLFWwindow* window, CameraSettings settings);
    mat4 getViewMatrix();
    mat4 getProjectionMatrix();
    vec3 getPosition();
    vec3 getForwardVector();
    vec3 getRightVector();

    void move(const vector<bool>& keys, const float& deltaTime);
    void changeTarget(const float& deltaX, const float& deltaY, const float& delta);
    void update(const vector<bool>& keys, const float& deltaX, const float& deltaY, const float& deltaTime);

    TransformComposite getTransform() const;
    void setTransform(const TransformComposite& transform);

    void addPosition(const vec3& newPosition);
    void addRotation(const vec3& rotationVec, const float& angle);

};

#endif
