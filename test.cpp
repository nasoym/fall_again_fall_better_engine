#include <stdio.h>
#include <string>
#include "math3d.h"
#include <windows.h>

int	getSecondsSinceLastWrite(){
	HANDLE hFile1;
	FILETIME ftCreate, ftAccess, ftWrite;
	LPCSTR fname1 = "watchdog.txt";

	hFile1 = CreateFile(fname1, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
	if(hFile1 == INVALID_HANDLE_VALUE) {
		printf("Could not open file, error %d\n", GetLastError());
		return -1;
	}

	if(!GetFileTime(hFile1, &ftCreate, &ftAccess, &ftWrite)) {
		printf("Something wrong lol!\n");
		return -1;
	}

	FILETIME currentTime;
	GetSystemTimeAsFileTime(&currentTime);

	__int64 intFileWriteTime = ((__int64)ftWrite.dwHighDateTime << 32) + ftWrite.dwLowDateTime;
	__int64 intCurrentTime = ((__int64)currentTime.dwHighDateTime << 32) + currentTime.dwLowDateTime;

	__int64 timeSinceLastWrite = intCurrentTime - intFileWriteTime;

	if(CloseHandle(hFile1) == 0) {
		printf("Can't close the file handle!\n");
		return -1;
	}

	return (int) (timeSinceLastWrite / 10000000);
}



void	shutdown(){
	printf("shutdown \n");
}


int main(int argc, char *argv[]) {
	printf("TESTING:\n");
	/*
	Sleep(1000);
	system("main.exe");
	*/

	int		secondsSinceLastWrite;
	int		errorCount = 0;
	int		maxFileErrorCount = 10;


	int		readInterval = 5;

	int		readError = 0;
	int		maxReadError = 3;

	while(true){
		Sleep(1000 * readInterval);

		secondsSinceLastWrite = getSecondsSinceLastWrite();
		if (secondsSinceLastWrite == -1) {
			if (errorCount > maxFileErrorCount ) {
				shutdown();
				errorCount = 0;
			}
			printf("get file time error\n");
			errorCount += 1;
			continue;
		}
		std::cout << ":" << secondsSinceLastWrite << "\n";
		if (secondsSinceLastWrite > readInterval) {
			readError += 1;
		}

		if (readError > maxReadError) {
			shutdown();
			readError = 0;
		}
	}

	return 0;
}

