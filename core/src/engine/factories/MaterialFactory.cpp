#include "MaterialFactory.hpp"
#include "shaderProgram.hpp"

const string vertex_shader = "vertex.glsl";
const string default_fragment = "fragment_main.glsl";
const string phong_blinn_fragment = "fragment_blinn_phong.glsl";
const string ambient_fragment = "fragment_ambient.glsl";

static MaterialFactory& MaterialFactory::getInstance()
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

    auto vertex_shader = ShaderFactory::createShader(GL_VERTEX_SHADER, configReader->getVertexShaderPath());
    switch(material_type)
    {

        case SHADER_DEFAULT:
            auto fragment_shader = ShaderFactory::createShader(GL_FRAGMENT_SHADER, path + default_fragment);
            ShaderProgram* shader_program = new ShaderProgram(vertex_shader, fragment_shader);

            shader_program->observe(camera);

            Materal* res = new Material(shader_program);
            return res;
        case SHADER_PHONG_BLINN:
            auto fragment_shader = ShaderFactory::createShader(GL_FRAGMENT_SHADER, path + phong_blinn_fragment);
            ShaderProgram* shader_program = new ShaderProgram(vertex_shader, fragment_shader);

            shader_program->observe(camera);

            Materal* res = new Material(shader_program);
            return res;
        case SHADER_AMBIENT:
            auto fragment_shader = ShaderFactory::createShader(GL_FRAGMENT_SHADER, path + ambient_fragment);
            ShaderProgram* shader_program = new ShaderProgram(vertex_shader, fragment_shader);

            shader_program->observe(camera);

            Materal* res = new Material(shader_program);
            return res;
        default:
            auto fragment_shader = ShaderFactory::createShader(GL_FRAGMENT_SHADER, path + default_fragment);
            ShaderProgram* shader_program = new ShaderProgram(vertex_shader, fragment_shader);

            shader_program->observe(camera);

            Materal* res = new Material(shader_program);
            return res;
    }
}

