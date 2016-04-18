#ifndef COMMON_H
#define COMMON_H

#include <QSemaphore>
#include "myConstants.h"

extern int buffer[BufferSize]; // Ring buffer

extern QSemaphore freeBytes; // Check for free bytes in the ring buffer
extern QSemaphore usedBytes; // Check for used bytes in the ring buffer

extern int Josh; // Used as a global variable where it is required in numerous threads
extern int plotvalue; // Global vatiable for plotting
extern int milk; // Global variable for amount of milk specified
extern int user_temperature; // Global variable for user selected temperature

#endif // COMMON_H
