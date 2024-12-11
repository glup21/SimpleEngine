#include "MaterialFactory.hpp"
#include "shaderProgram.hpp"
#include "shaderFactory.hpp"

const string vertex_shader = "vertex.glsl";
const string default_fragment = "fragment_main.glsl";
const string phong_blinn_fragment = "fragment_blinn_phong.glsl";
const string ambient_fragment = "fragment_ambient.glsl";

MaterialFactory::MaterialFactory() 
{

}

MaterialFactory& MaterialFactory::getInstance()
{

    static MaterialFactory s;
    return s;

}

void MaterialFactory::setCamera(Camera* camera)
{
    this->camera = camera;
}

void MaterialFactory::setShaderPath(string path)
{
    this->path = path;
}

Material* MaterialFactory::getMaterialInstance(int material_type)
{
    auto vertex_shader = ShaderFactory::createShader(GL_VERTEX_SHADER, path + "vertex.glsl");

    std::string fragment_path;
    switch (material_type)
    {
        case SHADER_PHONG_BLINN:
            fragment_path = phong_blinn_fragment;
            std::cout << "PHONG_BLINN!!!" << std::endl;
            break;
        case SHADER_AMBIENT:
            fragment_path = ambient_fragment;
            std::cout << "AMBIENT!!!" << std::endl;
            break;
        case SHADER_DEFAULT:
        default:
            fragment_path = default_fragment;
            std::cout << "DEFAULT!!!" << std::endl;
            break;
    }

    Shader* fragment_shader = ShaderFactory::createShader(GL_FRAGMENT_SHADER, path + fragment_path);

    ShaderProgram* shader_program = new ShaderProgram(vertex_shader, fragment_shader);
    shader_program->observe(camera);
    shader_programs.push_back(shader_program);
    std::cout << "Size: " <<  shader_programs.size() << std::endl;

    return new Material(shader_program);
}

void MaterialFactory::observeByShaderPrograms(Subject* subject)
{

    for( ShaderProgram* shader_program: shader_programs)
    {
        
        shader_program->observe(subject);
    }
        
}

void MaterialFactory::updateAllLights()
{
    for( ShaderProgram* shader_program: shader_programs)
    {
        
        shader_program->updateLight();
    }
}