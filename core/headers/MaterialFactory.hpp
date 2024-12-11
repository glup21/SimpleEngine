#ifndef MATERIAL_FACTORY_HPP
#define MATERIAL_FACTORY_HPP

#define SHADER_DEFAULT 0
#define SHADER_PHONG_BLINN 1
#define SHADER_AMBIENT 2
#define SHADER_COLOR 3

#include "Material.hpp"
#include "camera.hpp"
#include <string>
#include "IObserver.hpp"
#include <vector>

using std::string;

class MaterialFactory
{

private: 
    MaterialFactory();
    Camera* camera;
    string path;
    std::vector<ShaderProgram*> shader_programs;
    
public:
    static MaterialFactory& getInstance();

    void setCamera(Camera* camera);
    void setShaderPath(string path);
    Material* getMaterialInstance(int material_type);

    void observeByShaderPrograms(Subject* subject);
    void updateAllLights();

};

#endif