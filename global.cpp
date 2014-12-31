#include "global.h"

char buffer[MAX_BUFFER_SIZE];
QSemaphore freeBytes(MAX_BUFFER_SIZE);
QSemaphore usedBytes;
