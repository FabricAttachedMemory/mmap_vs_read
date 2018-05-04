#ifndef MEASURES_H
#define MEASURES_H
#include <cstdint>
#include <ctime>


class Measures {

    public:
        struct MemoryState {
            uint32_t virtualMem;
            uint32_t physicalMem;
        };

        double StartTimer();
        double StopTimer();
        MemoryState GetMemoryUsed();

    private:

        int parseProcStatusLine(char* line);
        double timerStartValue, timerStopValue;
};

#endif