// Provides render pipeline

#include "engine.h"

void Engine::init(Scene scene)
{

    drawObjectBuffer = scene.getObjects();

    for (IDrawableObject* obj : *drawObjectBuffer) {
        obj->setup();
    }


}

void Engine::run()
{

}
void Engine::shutdown()
{

}