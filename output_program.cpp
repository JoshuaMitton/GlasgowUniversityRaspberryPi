#include "output_program.h"
#include <QtCore>
#include <QDebug>
#include "common.h"
#include <QApplication>
#include <stdio.h>
#include <bcm2835.h>
#include <conproddialog.h>
// includes for Qt and GPIO


#define HEATER RPI_V2_GPIO_P1_11 // GPIO pin 11
#define PUMP1 RPI_V2_GPIO_P1_16 // GPIO pin 16
#define PUMP2 RPI_V2_GPIO_P1_13 // GPIO pin 13
#define PUMP3 RPI_V2_GPIO_P1_12// GPIO pin 12

output_program::output_program(QObject *parent) :
    QThread(parent)
{
}

void output_program::run() // run the thread
{
    qDebug() << "Output Thread Running!"; // State it is running

    bcm2835_init(); // initialize the library 

    bcm2835_gpio_fsel (HEATER, BCM2835_GPIO_FSEL_OUTP); // Set the LED as output
    bcm2835_gpio_fsel (PUMP1, BCM2835_GPIO_FSEL_OUTP); // Set the LED as output
    bcm2835_gpio_fsel (PUMP2, BCM2835_GPIO_FSEL_OUTP); // Set the LED as output
    bcm2835_gpio_fsel (PUMP3, BCM2835_GPIO_FSEL_OUTP); // Set the LED as output

    bcm2835_gpio_write(HEATER, LOW); // Set all Low
    bcm2835_gpio_write(PUMP1, LOW); // Set all Low
    bcm2835_gpio_write(PUMP2, LOW); // Set all Low
    bcm2835_gpio_write(PUMP3, LOW); // Set all Low

    bcm2835_delay(5000); // Wait for graph to initialise before running

    while (user_temperature <= plotvalue) // Wait for user to choose a reasonable value
    {
        qDebug() << "Increase Temperature"; // Say to choose
        bcm2835_delay(100); // Wait
    }

    qDebug() << "Heater is Starting!"; // Start heating good value is selected
     bcm2835_gpio_write(HEATER, HIGH); // Heater on

    // Wait for Water to Heat
    while (user_temperature > plotvalue) // Wait for the water to get to the selected value
    {
	qDebug() << "Heating"; // Say it is heating
        bcm2835_delay(100); // Wait a while, this will take a while to heat
    }

    // Turn off heater
    qDebug() << "Heater has turned off"; // heating done!
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

    bcm2835_gpio_write(HEATER, LOW); // set everything off just in case anything goes wrong!
    bcm2835_gpio_write(PUMP1, LOW);// set everything off just in case anything goes wrong!
    bcm2835_gpio_write(PUMP2, LOW);// set everything off just in case anything goes wrong!
    bcm2835_gpio_write(PUMP3, LOW);// set everything off just in case anything goes wrong!
}






