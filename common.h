#ifndef COMMON_H
#define COMMON_H

#include <QSemaphore>
#include "myConstants.h"

extern int buffer[BufferSize];

extern QSemaphore freeBytes;
extern QSemaphore usedBytes;

extern int Josh;
extern int plotvalue;
extern int milk;
extern int user_temperature;

#endif // COMMON_H
