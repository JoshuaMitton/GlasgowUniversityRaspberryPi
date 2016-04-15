#include "consumer.h"
#include "common.h"
#include <QtCore>
#include <conproddialog.h>

Consumer::Consumer(QObject *parent) :
    QThread(parent)
{
}

void Consumer::run()
{
    int value;
    for (int i = 0; i < DataSize; ++i) {
        usedBytes.acquire();
        value = buffer[i % BufferSize];
        freeBytes.release();
        emit bufferFillCountChanged(usedBytes.available());
        emit consumerCountChanged(i);
        Josh = value;
    }
}
