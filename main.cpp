
#include <stdio.h>
#include "logger.h"

#include "engine.h"
Engine* mEngine = 0;

int main(int argc, char *argv[]) {
    Logger::debug("running main");

    mEngine = new Engine();

    mEngine->run();
    mEngine->run();
    mEngine->run();
    mEngine->run();

    delete mEngine;

	return 0;
}
