
#include <stdio.h>
#include "logger.h"

#include "engine_physic.h"
#include "box_physic.h"

#include "engine_graphic.h"
#include "box_graphic.h"

PhysicsEngine*  physicsEngine = 0;
GraphicsEngine* graphicsEngine = 0;

int main(int argc, char *argv[]) {
    Logger::debug("running main");

    graphicsEngine = new GraphicsEngine();
    physicsEngine = new PhysicsEngine();

    graphicsEngine->render();
    physicsEngine->simulate(0.1f);
    graphicsEngine->render();
    physicsEngine->simulate(0.1f);

    delete physicsEngine;
    delete graphicsEngine;

	return 0;
}
