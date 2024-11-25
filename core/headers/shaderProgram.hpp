#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "shader.hpp"
#include <memory>
#include <string>
#include <vector>
#include "camera.hpp"
#include "IObserver.hpp"

using std::unique_ptr, std::string, std::vector, glm::vec3;

class Shader;
class Camera;

class ShaderProgram : public IObserver
{
private:
    vector<Shader*> shaders; //we dont need vector 
    GLuint ID;
    vector<vec3> lights;

    void checkLinkErrors();

public:
    ShaderProgram(Shader* vertexShader, Shader* fragmentShader);
    ~ShaderProgram();

    void attachShader(Shader* shader);
    void link();
    void use();

    //low level vs high level?
    void setMat4(const string& name, glm::mat4 value); // maybe add function for model matrix?
    void setInt(const string& name, int value);
    void setVec3(const string& name, glm::vec3 value);
    void setVec4(const string& name, glm::vec4 value);
    void setFloat(const string& name, float value);
    void setLight(int index, glm::vec3 position, glm::vec3 color, float brightness, int type);
    void setLightCount(int count);


    void update(Subject* subject) override;
    void observe(Subject* subject);
    void updateLight();


};

#endif