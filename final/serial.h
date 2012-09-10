#include "logger.h"
#include <windows.h>

HANDLE hComm;

void	initSerial(){
	hComm = CreateFile("COM1", 
		GENERIC_READ, 
		0, 
		0, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		0);

	if (hComm == INVALID_HANDLE_VALUE){
		Logger::debug("error opening port");
		return;
	}

	COMMTIMEOUTS timeouts={0};
	timeouts.ReadIntervalTimeout=100;
	timeouts.ReadTotalTimeoutConstant=100;
	timeouts.ReadTotalTimeoutMultiplier=20;
	SetCommTimeouts(hComm, &timeouts);
}

int		readSerial(){
	char szBuff[2] = {0};
	DWORD myBytesRead = 0;
	ReadFile(hComm, szBuff, 1, &myBytesRead, NULL);
	return szBuff[0];
}
