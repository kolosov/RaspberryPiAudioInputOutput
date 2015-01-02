#include "global.h"

qint16 buffer[MAX_BUFFER_SIZE];
QSemaphore freeBytes(MAX_BUFFER_SIZE);
QSemaphore usedBytes;
