#ifndef PRODUCER_H
#define PRODUCER_H

#include <QThread>
#include <QTime>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
// sets the clock for the AD converter
#include "gz_clk.h"

class Producer : public QThread
{
    Q_OBJECT
public:
    explicit Producer(QObject *parent = 0);
    void run();

    // ring buffer functions
    int hasSample();
    int getSample();

    // thread functions
    void quit();

protected: // functions used
    void writeReset(int fd);
    void writeReg(int fd, uint8_t v);
    uint8_t readReg(int fd);
    int readData(int fd);
    void initialise();

private:
    bool running;
    void pabort(const char *s);

    // file descriptor on the SPI interface
    int fd;

    // file descriptor on the interrupt pin
    int sysfs_fd;

    // data collected
    int *samples;

    // pointer to ringbuffer
    int *pIn;
    int *pOut;

    // spi constants for the ioctrl calls
    uint8_t mode;
    uint8_t bits;
    uint32_t speed;
    uint16_t delay;
    int drdy_GPIO;


signals:
    void bufferFillCountChanged(int bCount);
    void producerCountChanged(int count);

public slots:
};

#endif // PRODUCER_H
