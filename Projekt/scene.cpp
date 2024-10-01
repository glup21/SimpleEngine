#include "scene.h"

Scene::Scene(vector<IDrawableObject*> dObj) : drawObjects (dObj) {}
vector<IDrawableObject*>* Scene::getObjects() { return &drawObjects;}