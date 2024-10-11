#ifndef MODEL_H
#define MODEL_H

#include "mesh.hpp"
#include "shader.hpp"
#include "IGameObject.hpp"
#include "IDrawableObject.hpp"
#include <vector>
//object loader
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "imageLoader.hpp"
using std::vector;

class Model : public IGameObject, public IDrawableObject
{
public:
    Model(string path, string ID, Transform transform);

    void setup(Shader* shader) override;
    void draw(Shader* shader) override;
    void update(float delta) override;

    Transform getTransform() const override;
    void setTransform(const Transform& transform) override;

    void setPosition(const vec3& newPosition) override;
    void setRotation(const quat& newRotation) override;
    void setScale(const vec3& newScale) override;

    void addPosition(const vec3& addPosition) override;
    void addRotation(const quat& addRotation) override;

    mat4 getTransformMatrix() const override;
private:
    string ID;
    vector<Mesh> meshes;
    string directory;
    Transform transform;
    ImageLoader imageLoader;
    
    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         string typeName);



};

#endif