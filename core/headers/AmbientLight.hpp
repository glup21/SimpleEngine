#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "transformComposite.hpp"
#include "IGameObject.hpp"
#include "shaderProgram.hpp"
#include "ILight.hpp"
using glm::vec3, glm::mat4;

class AmbientLight : public ILight, public Subject {
private:
    TransformComposite transform;

public:
    AmbientLight(vec4 color = vec4(1.0f));
    ~AmbientLight() = default;

    void addPosition(const vec3& newPosition);
    mat4 getTransformMatrix();

    void update(float delta) override;

    //to make compiler shut up
    void addRotation(const vec3& rotationVec, const float& angle) override {}
    void addScale(const glm::vec3& newScale) override {}

};

#endif
