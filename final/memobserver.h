#include "logger.h"
#include <windows.h>
#include <psapi.h>

int	getMemoryUsageWorkingSize(){
	PROCESS_MEMORY_COUNTERS memCounter;
	bool result = GetProcessMemoryInfo(GetCurrentProcess(),
									   &memCounter,
									   sizeof( memCounter ));
  	return memCounter.WorkingSetSize;
}
