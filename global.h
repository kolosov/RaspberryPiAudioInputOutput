#ifndef GLOBAL_H
#define GLOBAL_H

#include <QSemaphore>

#define PRODUCER_DATA_SIZE 1000000000
#define MAX_BUFFER_SIZE 2048

extern char buffer[];
extern QSemaphore freeBytes;
extern QSemaphore usedBytes;

#endif // GLOBAL_H
