
#ifdef MACOSX
#elif WIN
    #include <windows.h>
#else
#endif

#include <stdio.h>
#include "engine.h"
Engine* mEngine = 0;

int main(int argc, char *argv[]) {

    mEngine = new Engine();

	//printf("before initial wait of 20 seconds\n");
	//Sleep(1000 * 20);
	//printf("after initial wait\n");

	mEngine->runPython();
    mEngine->run();
    delete mEngine;
	
	return 0;

}
