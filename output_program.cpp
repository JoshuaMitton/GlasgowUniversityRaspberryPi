#include "output_program.h"
#include <QtCore>
#include <QDebug>
#include "common.h"
#include <QApplication>
#include <stdio.h>
#include <bcm2835.h>
#include <conproddialog.h>

#define HEATER RPI_V2_GPIO_P1_11
#define PUMP1 RPI_V2_GPIO_P1_16
#define PUMP2 RPI_V2_GPIO_P1_13
#define PUMP3 RPI_V2_GPIO_P1_12

output_program::output_program(QObject *parent) :
    QThread(parent)
{
}

void output_program::run()
{
    qDebug() << "Output Thread Running!";

    bcm2835_init(); // initialize the library

    bcm2835_gpio_fsel (HEATER, BCM2835_GPIO_FSEL_OUTP); // Set the LED as output
    bcm2835_gpio_fsel (PUMP1, BCM2835_GPIO_FSEL_OUTP); // Set the LED as output
    bcm2835_gpio_fsel (PUMP2, BCM2835_GPIO_FSEL_OUTP); // Set the LED as output
    bcm2835_gpio_fsel (PUMP3, BCM2835_GPIO_FSEL_OUTP); // Set the LED as output

    bcm2835_gpio_write(HEATER, LOW);
    bcm2835_gpio_write(PUMP1, LOW);
    bcm2835_gpio_write(PUMP2, LOW);
    bcm2835_gpio_write(PUMP3, LOW);

    bcm2835_delay(5000);

    while (user_temperature <= plotvalue)
    {
        qDebug() << "Increase Temperature";
        bcm2835_delay(100);
    }

    qDebug() << "Heater is Starting!";
     bcm2835_gpio_write(HEATER, HIGH);

    // Wait for Water to Heat
    while (user_temperature > plotvalue)
    {
	qDebug() << "Heating";
        bcm2835_delay(100);
    }

    // Turn off heater
    qDebug() << "Heater has turned off";
    bcm2835_gpio_write(HEATER, LOW);

    // Pump 1 on for 1 second
    bcm2835_gpio_write(PUMP3, HIGH);
    bcm2835_delay(6000);
    qDebug() << "Pump 1 is pumping";
    bcm2835_gpio_write(PUMP3, LOW);

   //  Wait for tea to brew 20 seconds
    qDebug() << "Tea is brewing!!";
    bcm2835_delay(15000);
    qDebug() << "Tea is brewed!!";

   //  Pump 2 on for 1 second
    bcm2835_gpio_write(PUMP2, HIGH);
    qDebug() << "Pump 2 is pumping!";
    bcm2835_delay(4700);
    bcm2835_gpio_write(PUMP2, LOW);

    qDebug() << milk;
    // Pump 3 for milk selection
    if (milk > 0)
    {
    bcm2835_gpio_write(PUMP1, HIGH);
    qDebug() << "Milk is pumping!";
    bcm2835_delay(200*milk);           //0.5 second per milk serving
    bcm2835_gpio_write(PUMP1, LOW);
    }

    qDebug() << "TEA READY :)";

    bcm2835_gpio_write(HEATER, LOW);
    bcm2835_gpio_write(PUMP1, LOW);
    bcm2835_gpio_write(PUMP2, LOW);
    bcm2835_gpio_write(PUMP3, LOW);
}






