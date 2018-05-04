#include <stdio.h>
#include <string.h>
#include <fstream>

#include "../headers/measures.h"

using namespace std;


Measures::MemoryState Measures::GetMemoryUsed(){
	FILE *file = fopen("/proc/self/status", "r");
	char line[128];
	MemoryState processMem;

	while (fgets(line, 128, file) != NULL) {
		if (strncmp(line, "VmSize:", 7) == 0) {
			processMem.virtualMem = parseProcStatusLine(line);
			break;
		}

		if (strncmp(line, "VmRSS:", 6) == 0) {
			processMem.physicalMem = parseProcStatusLine(line);
			break;
		}
	}
	fclose(file);
	return processMem;
}//GetMemoryUsed


int Measures::parseProcStatusLine(char* line){
	// This assumes that a digit will be found and the line ends in " Kb".
	int i = strlen(line);
	const char *p = line;
	while (*p < '0' || *p > '9') p++;
	line[i - 3] = '\0';
	i = atoi(p);
	return i;
}//parseProcStatusLine


double Measures::StartTimer(){
    this->timerStartValue = clock();
    return this->timerStartValue;
}//StartTimer


double Measures::StopTimer(){
    double endTime = clock();
    this->timerStopValue = (endTime - this->timerStartValue) / double(CLOCKS_PER_SEC);
    return this->timerStopValue;
}//StopTimer