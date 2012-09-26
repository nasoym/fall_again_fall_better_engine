
#include <windows.h>
#include "engine.h"
Engine* mEngine = 0;

int main(int argc, char *argv[]) {

	//system("shutdown /i /?");
    mEngine = new Engine();
	mEngine->runPython();
    mEngine->run();
    delete mEngine;
	
	return 0;

}
