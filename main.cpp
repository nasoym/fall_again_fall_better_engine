
#include <stdio.h>
#include "logger.h"
#include "uuid.h"

#include "engine.h"
Engine* mEngine = 0;

int main(int argc, char *argv[]) {
    Logger::debug("running main.");

	Uuid* uuid = new Uuid();
	printf("hello: %s \n",uuid->toString().c_str());

	return 0;

    mEngine = new Engine();

    mEngine->run();

    delete mEngine;

	return 0;
}
