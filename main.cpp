
#include "engine.h"
Engine* mEngine = 0;

int main(int argc, char *argv[]) {
    mEngine = new Engine();
	mEngine->runPython();
    mEngine->run();
    delete mEngine;
	return 0;
}
