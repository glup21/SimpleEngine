#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "ILight.hpp"
#include "transformComposite.hpp"
#include "shaderProgram.hpp"
#include "glm/glm.hpp"

using glm::vec3, glm::mat4, glm::vec4;

class SpotLight : public ILight, public Subject {
private:
    float distance; 
    float angle;

public:
    SpotLight(vec4 color = vec4(1.0f), float distance = 10.0f, float angle = 45.0f); 
    ~SpotLight() = default;

    void addPosition(const vec3& newPosition) override;  
    mat4 getTransformMatrix() override;  

    void update(float delta) override;

    float getDistance() const { return distance; }
    void setDistance(float newDistance) { distance = newDistance; notifyObservers(); }

    void addRotation(const glm::vec3& rotationVec, const float& angle) override;
    void addScale(const glm::vec3& newScale) override {}

    float getAngle() { return angle;}

};

#endif
