#ifndef PRODUCER_H
#define PRODUCER_H

#include <QCoreApplication>
#include <QObject>
#include <QThread>
#include <QTime>
#include "global.h"
#include <stdio.h>

class Producer : public QThread
{
public:
    void run()
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        for (int i = 0; i < PRODUCER_DATA_SIZE; ++i) {
            freeBytes.acquire();
            int subscript = i % MAX_BUFFER_SIZE;
            buffer[subscript] = "ACGT"[(int)qrand() % 4];
            usedBytes.release();
        }
    }
};

#endif // PRODUCER_H
