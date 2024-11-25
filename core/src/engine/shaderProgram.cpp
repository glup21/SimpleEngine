#include "shaderProgram.hpp"
#include "pointLight.hpp"
#include "AmbientLight.hpp"
#include <stdio.h>
#include <GL/glu.h>


ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader) : ID(glCreateProgram()) 
{
    
    attachShader(vertexShader);
    attachShader(fragmentShader);
    link();
}
ShaderProgram::~ShaderProgram() { glDeleteProgram(ID); }

void ShaderProgram::attachShader(Shader* shader) {
    glAttachShader(ID, shader->getID());
    shaders.push_back(shader);
}

void ShaderProgram::link() {
    glLinkProgram(ID);
    checkLinkErrors();
}

void ShaderProgram::use() { glUseProgram(ID); }

void ShaderProgram::checkLinkErrors() {
    GLint success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(ID, 1024, NULL, infoLog);
        std::cerr << "ERROR: SHADER LINKING ERROR: " << infoLog << std::endl;
    }
}

void ShaderProgram::setMat4(const std::string& name, glm::mat4 value) 
{

    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        //std::cerr << "Warning: Uniform '" << name << "' not found.\n";
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::setInt(const std::string& name, int value) 
{
    use();
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        //std::cerr << "Warning: Uniform '" << name << "' not found.\n";
        return;
    }
    if(name == "lightsCount")
        std::cout << "Lights count in setInt: " << value << std::endl; 
    glUniform1i(location, value);
    
}

void ShaderProgram::setVec3(const std::string& name, glm::vec3 value) 
{

    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        //std::cerr << "Warning: Uniform '" << name << "' not found.\n";
        return;
    }
    std::cout <<name << ": Location: " << location << std::endl;
    use();
    glUniform3f(location, 1.0f, 2.0f, 0.0f);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << gluErrorString(error) << std::endl;
    }
}

void ShaderProgram::setVec4(const std::string& name, glm::vec4 value) 
{

    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        //std::cerr << "Warning: Uniform '" << name << "' not found.\n";
        return;
    }
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::setLight(int index, glm::vec3 position, glm::vec3 color, float brightness, int type) 
{
    string base = "lights[" + std::to_string(index) + "]";
    setVec3(base, position);
}

void ShaderProgram::setLightCount(int count) 
{
    setInt("lightsCount", count);
}

void ShaderProgram::update(Subject* subject) 
{

    
    Camera* camera = dynamic_cast<Camera*>(subject);
    if (camera) 
    {
        setMat4("viewMatrix", camera->getViewMatrix());
        setMat4("projectionMatrix", camera->getProjectionMatrix());
        setVec3("cameraPosition", camera->getPosition());

        return;
    }

    PointLight* pointLight = dynamic_cast<PointLight*>(subject);
    if (pointLight) 
    {
        std::cout << "Point light added!\n" << std::endl;
        lights.push_back(pointLight->getTransformMatrix()[3]);
        updateLight();
        //updateLight();
        //setLight(1, pointLight->getTransformMatrix()[3], vec3(1.0), 1.0, 1);

        // std::cout << pointLight->getTransformMatrix()[3].x << pointLight->getTransformMatrix()[3].y << pointLight->getTransformMatrix()[3].z << std::endl;
        // setInt("lightsCount", lights.size());
        // setVec3("lights[0]", pointLight->getTransformMatrix()[3]);
        return;
    }

    AmbientLight* ambientLight = dynamic_cast<AmbientLight*>(subject);
    if (ambientLight) 
    {
        std::cout << "Ambient light added!\n" << std::endl;
        lights.push_back(ambientLight->getTransformMatrix()[3]);
        updateLight();
        //updateLight();
        //setLight(1, vec3(0.0, 0.0, 0.0), vec3(1.0), 1.0, 0);

        // std::cout << "Lights vector size: " << std::endl;
        // setInt("lightsCount", lights.size());
        // glUniform3fv(glGetUniformLocation(ID, "lights[1]"), lights.size(), lights.data());

        return;
    }

}

void ShaderProgram::updateLight()
{
    printf("Test\n");
    glm::vec4 lp = glm::vec4(1.0, 0.0, 0.0, 1.0);
    GLint idLightPos = glGetUniformLocation(ID, "lights[0].color");
    if (idLightPos < 0) {
        printf("The variable does not exist.");
    }
    else {
        glUseProgram(ID);
        glUniform4f(idLightPos, lp.x, lp.y, lp.z, lp.w);
        glUseProgram(0);
    }


    lp = glm::vec4(1.0, 0.0, 0.0, 1.0);
    idLightPos = glGetUniformLocation(ID, "lights[2].color");
    if (idLightPos < 0) {
        printf("The variable does not exist.");
    }
    else {
        glUseProgram(ID);
        glUniform4f(idLightPos, lp.x, lp.y, lp.z, lp.w);
        glUseProgram(0);
    }

    // glUseProgram(ID);
    // for(int i = 0; i < lights.size(); i++)
    // {
        
    //     char location[64];
    //     sprintf(location, "lights[%d]", i);
    //     printf("%f %f %f\n", lights[i].x, lights[i].y, lights[i].z);

    //     setVec3(location, lights[i]);


    // }
}

void ShaderProgram::observe(Subject* subject) 
{
    subject->addObserver(this);
}
