#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "shader.hpp"
#include <memory>
#include <string>
#include <vector>
#include "camera.hpp"
#include "IObserver.hpp"

using std::unique_ptr, std::string, std::vector;

class Shader;
class Camera;

class ShaderProgram : public IObserver
{
private:
    vector<Shader*> shaders; //we dont need vector 
    GLuint ID;
    Camera* camera;

    void checkLinkErrors();

public:
    ShaderProgram(Camera* camera);
    ~ShaderProgram();

    void attachShader(Shader* shader);
    void link();
    void use();

    //low level vs high level?
    void setMat4(const string& name, glm::mat4 value); // maybe add function for model matrix?
    void setInt(const string& name, int value);
    void setVec3(const string& name, glm::vec3 value);

    void update() override;
    void subscribe();


};

#endif