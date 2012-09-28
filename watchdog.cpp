#include <stdio.h>
#include <string>

#include <windows.h>

#include <Ogre.h>
using namespace Ogre;

#include <time.h>

#include "boost/format.hpp"
using boost::format;

void setupLogging(){
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	char buffer [50];
	strftime(buffer,50,"logs/%Y_%m_%d_%H_%M_%S_watchdog.log",timeinfo);

	LogManager*     mLogger;
    mLogger = new Ogre::LogManager();

	bool	ogreLogSupressFileOutput = false;
	bool	ogreLogDebuggerOutput = true;
	bool	ogreLogDefaultLog = false;
    mLogger->createLog(buffer,
		ogreLogSupressFileOutput,
		ogreLogDebuggerOutput,
		ogreLogDefaultLog);

	mLogger->setLogDetail(LL_LOW);
	//mLogger->setLogDetail(LL_NORMAL);
	//mLogger->setLogDetail(LL_BOREME);
}

void log(std::string message) {
	LogManager::getSingleton().logMessage(message,LML_CRITICAL);
}

void log(format message) {
    log(message.str());
}

void log(char * text) {
	LogManager::getSingleton().logMessage(text,LML_CRITICAL);
}

int	getSecondsSinceLastWrite(){
	HANDLE hFile1;
	FILETIME ftCreate, ftAccess, ftWrite;
	LPCSTR fname1 = "watchdog.txt";

	hFile1 = CreateFile(fname1, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
	if(hFile1 == INVALID_HANDLE_VALUE) {
		log( format("Could not open file, error %1%") % GetLastError() );
		return -1;
	}

	if(!GetFileTime(hFile1, &ftCreate, &ftAccess, &ftWrite)) {
		log("Something wrong lol!");
		return -1;
	}

	FILETIME currentTime;
	GetSystemTimeAsFileTime(&currentTime);

	__int64 intFileWriteTime = ((__int64)ftWrite.dwHighDateTime << 32) + ftWrite.dwLowDateTime;
	__int64 intCurrentTime = ((__int64)currentTime.dwHighDateTime << 32) + currentTime.dwLowDateTime;

	__int64 timeSinceLastWrite = intCurrentTime - intFileWriteTime;

	if(CloseHandle(hFile1) == 0) {
		log("Can't close the file handle!");
		return -1;
	}

	return (int) (timeSinceLastWrite / 10000000);
}

void	shutdown(){
	log("shutdown");
	sleep(100);
	//system("shutdown -r");
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	setupLogging();
	log("start watchdog");

	int		secondsSinceLastWrite;
	int		errorCount = 0;
	int		maxFileErrorCount = 10;

	int		readInterval = 60 * 3;

	int		readError = 0;
	int		maxReadError = 2;

	//int		initialWait = 60 * 5;
	int		initialWait = 15;

	Sleep(1000 * initialWait);

	while(true){
		Sleep(1000 * readInterval);

		secondsSinceLastWrite = getSecondsSinceLastWrite();
		if (secondsSinceLastWrite == -1) {
			if (errorCount > maxFileErrorCount ) {
				errorCount = 0;
				shutdown();
				//break;
			}
			log("get file time error");
			errorCount += 1;
			continue;
		} else {
			errorCount = 0;
		}
		log(format(": %1%") % secondsSinceLastWrite);
		if (secondsSinceLastWrite > readInterval) {
			log("got read error");
			readError += 1;
		} else {
			readError = 0;
		}

		if (readError > maxReadError) {
			// test if file contains exit reason
			readError = 0;
			shutdown();
			//break;
		}
	}

	log("end watchdog");
	return 0;
}

