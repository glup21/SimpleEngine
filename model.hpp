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
using std::vector;

class Model : public IGameObject, public IDrawableObject
{
public:
    Model(string path);

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
    vector<Mesh> meshes;
    string directory;
    Transform transform;

    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         string typeName);


//     Mesh* mesh;
//     Transform transform;
//     Shader* shader;


// public:
//     Model(Mesh* m, Shader* sp);
//     ~Model() = default;

//     Mesh* getMesh();

//     void draw(Shader* shader = nullptr) override;
//     void setup(Shader* shader = nullptr) override;



};

#endif