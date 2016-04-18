#include "producer.h"
#include "common.h"
#include <QDebug>
#include <QtCore>
#include "gpio-sysfs.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <assert.h>
// All includes needed for storing to ring buffer using Qt


#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#define MAX_SAMPLES 65536 // mas size

Producer::Producer(QObject *parent) :
    QThread(parent)
{
}





void Producer::writeReset(int fd)
{
        int ret;
        uint8_t tx1[5] = {0xff,0xff,0xff,0xff,0xff}; // initialize
        uint8_t rx1[5] = {0}; // initialize
        struct spi_ioc_transfer tr; // storage structure
    tr.tx_buf = (unsigned long)tx1; // store to tx
    tr.rx_buf = (unsigned long)rx1; // store to rx
    tr.len = ARRAY_SIZE(tx1); // length of buffer
    tr.delay_usecs = delay; // delay
    tr.speed_hz = speed; // speed 
    tr.bits_per_word = bits; // number of bits

        ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
        if (ret < 1)
                pabort("can't send spi message"); // error is no spi message can pass
}


void Producer::writeReg(int fd, uint8_t v) // writing to the register
{
  int ret;
  uint8_t tx1[1];
  tx1[0] = v;
  uint8_t rx1[1] = {0};
  struct spi_ioc_transfer tr;
  tr.tx_buf = (unsigned long)tx1;
  tr.rx_buf = (unsigned long)rx1;
  tr.len = ARRAY_SIZE(tx1);
  tr.delay_usecs = delay;
  tr.speed_hz = speed;
  tr.bits_per_word = bits;

        ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
        if (ret < 1)
                pabort("can't send spi messageFAIL");

}

uint8_t Producer::readReg(int fd) // reading from the resigster
{
        int ret;
        uint8_t tx1[1];
        tx1[0] = 0;
        uint8_t rx1[1] = {0};
        struct spi_ioc_transfer tr;
    tr.tx_buf = (unsigned long)tx1;
    tr.rx_buf = (unsigned long)rx1;
    tr.len = ARRAY_SIZE(tx1);
    tr.delay_usecs = delay;
    tr.speed_hz = speed;
    tr.bits_per_word = 8;

        ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
        if (ret < 1)
          pabort("can't send spi message");

        return rx1[0];
}

int Producer::readData(int fd) // reading the actual data
{
        int ret;
        uint8_t tx1[2] = {0,0};
        uint8_t rx1[2] = {0,0};
        struct spi_ioc_transfer tr;
    tr.tx_buf = (unsigned long)tx1;
    tr.rx_buf = (unsigned long)rx1;
    tr.len = ARRAY_SIZE(tx1);
    tr.delay_usecs = delay;
    tr.speed_hz = speed;
    tr.bits_per_word = 8;

        ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
        if (ret < 1)
          pabort("can't send spi message");
        return (rx1[0]<<8)|(rx1[1]);
}

void Producer::initialise() // initializing the ADC
{
    int ret = 0;

    // SPI constants
    static const char *device = "/dev/spidev0.0";
    mode = SPI_CPHA | SPI_CPOL;
    bits = 8;
    speed = 50000;
    delay = 10;
    drdy_GPIO = 22;

    // open SPI device
    fd = open(device, O_RDWR);
    if (fd < 0)
      pabort("can't open device");

    /*
     * spi mode
     */
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1)
      pabort("can't set spi mode");

    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if (ret == -1)
      pabort("can't get spi mode");

    /*
     * bits per word
     */
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1)
      pabort("can't set bits per word");

    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1)
      pabort("can't get bits per word");

    /*
     * max speed hz
     */
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1)
      pabort("can't set max speed hz");

    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1)
      pabort("can't get max speed hz");

    fprintf(stderr, "spi mode: %d\n", mode);
    fprintf(stderr, "bits per word: %d\n", bits);
    fprintf(stderr, "max speed: %d Hz (%d KHz)\n", speed, speed/1000);

    // enable master clock for the AD
    // divisor results in roughly 4.9MHz
    // this also inits the general purpose IO
    gz_clock_ena(GZ_CLK_5MHz,5);

    // enables sysfs entry for the GPIO pin
    gpio_export(drdy_GPIO);
    // set to input
    gpio_set_dir(drdy_GPIO,0);
    // set interrupt detection to falling edge
    gpio_set_edge(drdy_GPIO,"falling");
    // get a file descriptor for the GPIO pin
    sysfs_fd = gpio_fd_open(drdy_GPIO);

    // resets the AD7705 so that it expects a write to the communication register
    writeReset(fd);

    // tell the AD7705 that the next write will be to the clock register
    writeReg(fd,0x20);
    // write 00001100 : CLOCKDIV=1,CLK=1,expects 4.9152MHz input clock
    writeReg(fd,0x0C);

    // tell the AD7705 that the next write will be the setup register
    writeReg(fd,0x10);
    // intiates a self calibration and then after that starts converting
    writeReg(fd,0x40);
}

void Producer::run() // run the ADC
{
        initialise();

        qsrand(QTime(0,0,0).secsTo(QTime::currentTime())); // reset time to 0

        running = true;
        fprintf(stderr,"We are running!\n");

        int i = 0;

        while (running) {

          // let's wait for data for max one second
          int ret = gpio_poll(sysfs_fd,1000); // poll data
          if (ret<1) {
            fprintf(stderr,"Poll error %d\n",ret);
          }
          // tell the AD7705 to read the data register (16 bits)
          writeReg(fd,0x38);
          // read the data register by performing two 8 bit reads
          Josh = readData(fd)-0x8000;

          freeBytes.acquire(); // check for free space
          buffer[i % BufferSize] = Josh; // store to buffer
          usedBytes.release(); // release data
          if(i % 20 == 0)
          emit bufferFillCountChanged(usedBytes.available());
          emit producerCountChanged(i);
          i++;
          if (i == DataSize)
          {
              i = 0;
          }
        }

        close(fd);
        gpio_fd_close(sysfs_fd);

}

int Producer::hasSample() // check if sample exists
{
  return (pOut!=pIn);
}


void Producer::quit() // exit
{
    running = false;
    exit(0);
}

void Producer::pabort(const char *s)
{
        perror(s);
        abort();
}


