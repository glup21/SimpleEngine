#include "shaderProgram.hpp"
#include "pointLight.hpp"
#include "AmbientLight.hpp"
#include "SpotLight.hpp"
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
use();
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
use();
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        //std::cerr << "Warning: Uniform '" << name << "' not found.\n";
        return;
    }
    use();
    glUniform3f(location, 1.0f, 2.0f, 0.0f);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << gluErrorString(error) << std::endl;
    }
}

void ShaderProgram::setVec4(const std::string& name, glm::vec4 value) 
{
    use();
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        //std::cerr << "Warning: Uniform '" << name << "' not found.\n";
        return;
    }
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::setLight(int index, glm::vec3 position, glm::vec3 color, float brightness, int type) 
{
    use();
    string base = "lights[" + std::to_string(index) + "]";
    setVec3(base, position);
}

void ShaderProgram::setLightCount(int count) 
{
    use();
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
        lights.push_back(pointLight);
        //updateLight();
        return;
    }

    AmbientLight* ambientLight = dynamic_cast<AmbientLight*>(subject);
    if (ambientLight) 
    {
        std::cout << "Ambient light added!\n" << std::endl;
        char location[64];
        lights.push_back(ambientLight);
        return;
    }

    SpotLight* spotLight = dynamic_cast<SpotLight*>(subject);
    if(spotLight)
    {
        std::cout << "Spot light added!\n" << std::endl;
        lights.push_back(spotLight);
        return;
    }
}

void ShaderProgram::updateLight()
{
    setLightCount(lights.size());
    use();
    for(int i = 0; i < lights.size(); i++)
    {
        printf("Test\n");
        if(lights[i]->getType() == 1) //Point light
        {
            PointLight* pointLight = dynamic_cast<PointLight*>(lights[i]);
            char location[64];
            //Color
            sprintf(location, "lights[%d].color", i);

            GLint idLightPos = glGetUniformLocation(ID, location);
            if (idLightPos < 0) {
                printf("The variable color does not exist.");
            }
            else 
            {
                glUseProgram(ID);
                vec4 lightColor = pointLight->getColor();
                glUniform4f(idLightPos, lightColor.x, lightColor.y, lightColor.z, lightColor.w);
                glUseProgram(0);
            }

            //Position

            sprintf(location, "lights[%d].position", i);

            idLightPos = glGetUniformLocation(ID, location);
            if (idLightPos < 0) {
                printf("The variable position does not exist.");
            }
            else 
            {
                glUseProgram(ID);
                vec3 lightPosition = pointLight->getTransformMatrix()[3];
                glUniform3f(idLightPos, lightPosition.x, lightPosition.y, lightPosition.z);
                glUseProgram(0);
            }

            // Distance

            sprintf(location, "lights[%d].distance", i);

            idLightPos = glGetUniformLocation(ID, location);
            if (idLightPos < 0) {
                printf("The variable distance does not exist.");
            }
            else 
            {
                glUseProgram(ID);

                float distance = pointLight->getDistance();
                glUniform1f(idLightPos, distance);
                //setFloat(location, distance);
                glUseProgram(0);
            }

            sprintf(location, "lights[%d].type", i);

            idLightPos = glGetUniformLocation(ID, location);
            if (idLightPos < 0) {
                printf("The variable distance does not exist.");
            }
            else 
            {
                glUseProgram(ID);
                glUniform1i(idLightPos, pointLight->getType());
                //setFloat(location, distance);
                glUseProgram(0);
            }
        }
        if(lights[i]->getType() == 0)
        {
            AmbientLight* ambientLight = dynamic_cast<AmbientLight*>(lights[i]);
            char location[64];
            sprintf(location, "ambientLight");

            GLint idLightPos = glGetUniformLocation(ID, location);
            if (idLightPos < 0) {
                printf("The variable color does not exist.");
            }
            else 
            {
                glUseProgram(ID);
                vec4 lightColor = ambientLight->getColor();
                std::cout << lightColor.r << lightColor.g << lightColor.b << lightColor.w << std::endl;
                glUniform4f(idLightPos, lightColor.x, lightColor.y, lightColor.z, lightColor.w);
                glUseProgram(0);
            }
        }

        if(lights[i]->getType() == 2) //Spot light
        {
            SpotLight* spotLight = dynamic_cast<SpotLight*>(lights[i]);
            char location[64];
            //Color
            sprintf(location, "lights[%d].color", i);

            GLint idLightPos = glGetUniformLocation(ID, location);
            if (idLightPos < 0) {
                printf("The variable color does not exist.");
            }
            else 
            {
                glUseProgram(ID);
                vec4 lightColor = spotLight->getColor();
                glUniform4f(idLightPos, lightColor.x, lightColor.y, lightColor.z, lightColor.w);
                glUseProgram(0);
            }

            //Position

            sprintf(location, "lights[%d].position", i);

            idLightPos = glGetUniformLocation(ID, location);
            if (idLightPos < 0) {
                printf("The variable position does not exist.");
            }
            else 
            {
                glUseProgram(ID);
                vec3 lightPosition = spotLight->getTransformMatrix()[3];
                glUniform3f(idLightPos, lightPosition.x, lightPosition.y, lightPosition.z);
                glUseProgram(0);
            }

            // Rotation

            sprintf(location, "lights[%d].rotation", i);

            idLightPos = glGetUniformLocation(ID, location);
            if (idLightPos < 0) {
                printf("The variable rotation does not exist.");
            }
            else 
            {
                glUseProgram(ID);
                vec3 lightPosition = spotLight->getTransformMatrix()[2];
                glUniform3f(idLightPos, lightPosition.x, lightPosition.y, lightPosition.z);
                glUseProgram(0);
            }

            // Distance

            sprintf(location, "lights[%d].distance", i);

            idLightPos = glGetUniformLocation(ID, location);
            if (idLightPos < 0) {
                printf("The variable distance does not exist.");
            }
            else 
            {
                glUseProgram(ID);

                float distance = spotLight->getDistance();
                glUniform1f(idLightPos, distance);
                //setFloat(location, distance);
                glUseProgram(0);
            }

            sprintf(location, "lights[%d].angle", i);

            idLightPos = glGetUniformLocation(ID, location);
            if (idLightPos < 0) {
                printf("The variable angle does not exist.");
            }
            else 
            {
                glUseProgram(ID);

                glUniform1f(idLightPos, glm::radians(spotLight->getAngle()));
                //setFloat(location, distance);
                glUseProgram(0);
            }
                sprintf(location, "lights[%d].type", i);

            idLightPos = glGetUniformLocation(ID, location);
            if (idLightPos < 0) {
                printf("The variable type does not exist.");
            }
            else 
            {
                glUseProgram(ID);
                glUniform1i(idLightPos, spotLight->getType());
                //setFloat(location, distance);
                glUseProgram(0);
            }
        }


    }
}

void ShaderProgram::observe(Subject* subject) 
{
    subject->addObserver(this);
}
