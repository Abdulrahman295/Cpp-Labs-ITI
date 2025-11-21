#include "delay.h"
#ifdef _WIN32
#include <windows.h>

void delay(float seconds) {
    DWORD milliseconds = (DWORD)(seconds * 1000);
    Sleep(milliseconds);
}

#else
#include <unistd.h>

void delay(float seconds) {
    useconds_t microseconds = (useconds_t)(seconds * 1000000);
    usleep(microseconds);
}

#endif