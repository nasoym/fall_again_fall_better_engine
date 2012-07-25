
#include <stdio.h>
#include "logger.h"
#include "uuid.h"

#include "engine.h"
Engine* mEngine = 0;

int main(int argc, char *argv[]) {
    Logger::debug("running main.");

    mEngine = new Engine();

	mEngine->runPython();
    mEngine->run();

    delete mEngine;

	return 0;
}
