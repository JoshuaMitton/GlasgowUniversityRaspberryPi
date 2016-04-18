#include "conproddialog.h"
#include "ui_conproddialog.h"
#include "myConstants.h"
#include <string.h>
#include <stdio.h>
#include <QFile>
#include <cmath>
#include <QTextStream>
#include <QObject>
// All neccessary files included

// BufferSize: maximum bytes that can be stored
char buffer[BufferSize]; // Buffer is required
int Josh;
int milk;
int user_temperature;
int plotvalue; // All global variables used here

QSemaphore freeBytes(BufferSize); // Buffer checks
QSemaphore usedBytes; // Buffer checks


ConProdDialog::ConProdDialog() : plot( QString("Tea") ), usertemp(10), actualtemp(15), usermilk(0) // Values needed in this thread
{
    this->setStyleSheet("background-color: white;"); // Want a white background

    // set up the gain knob
    knob.setValue(usertemp);
    knob.setRange(20, 100, 5);
    knob.setKnobWidth(200);
    knob.setFont( QFont("verdana", 14) );
    knob.setMarkerSize(10);
    // knob set up values, incl title markers, etc

    // use the Qt signals/slots framework to update the gain -
    // every time the knob is moved, the settemp function will be called
    connect( &knob, SIGNAL(valueChanged(double)), SLOT(settemp(double)) );

    // set up the gain knob
    knob2.setValue(usermilk);
    knob2.setRange(0, 4, 1);
    knob2.setKnobWidth(200);
    knob2.setFont( QFont("verdana", 14) );
    knob2.setMarkerSize(10);
    //second knob set up for use with user milk selection

    // use the Qt signals/slots framework to update the gain -
    // every time the knob is moved, the setmilk function will be called
    connect( &knob2, SIGNAL(valueChanged(double)), SLOT(setmilk(double)) );


    // set up the initial plot data with two curves on it
    for( int index=0; index<plotDataSize; ++index )
    {
        x1[index] = index;
        y1[index] = usertemp;
        x2[index] = index;
        y2[index] = actualtemp;
    }

    // make a plot curve from the first and second data and attach it to the plot
    curve1.setSamples(x1, y1, plotDataSize);
    curve1.setPen(* new QPen(Qt::red));
    curve1.attach(&plot);
    curve2.setSamples(x2, y2, plotDataSize);
    curve2.setPen(* new QPen(Qt::black));
    curve2.attach(&plot);

    plot.setAxisScale(QwtPlot::yLeft,0,100,10); // Set plot limits
    plot.replot();
    plot.show();

    // set up the layout - knob above thermometer
    vLayout.addWidget(&knob);
    vLayout.addWidget(&knob2);


    // plot to the left of knob and thermometer
    hLayout.addLayout(&vLayout);
    hLayout.addWidget(&plot);

    setLayout(&hLayout);

    // make three threads
    mProducer = new Producer(this);
    mConsumer = new Consumer(this);
    moutput_program = new output_program(this);

    // Start threads
    mProducer->start();
    mConsumer->start();
    moutput_program->start();

}

void ConProdDialog::timerEvent( QTimerEvent * ) // Called as the timer event for the plot
{

    double knobVal = usertemp; // Giving knob its correct value
    double knob2Val = usermilk; // Giving knob its correct value

    user_temperature = knobVal;
    milk = knob2Val;

    if (Josh != 0 ){ // If there is a new value, use it!
        //qDebug() << "Update Graph - next line is Josh value";
        plotvalue = (((((-0.000000000024463 * Josh) + 0.000001536757) * Josh) - 0.0350361) * Josh ) + 344.65;
        Josh = (((((-0.000000000024463 * Josh) + 0.000001536757) * Josh) - 0.0350361) * Josh ) + 344.65; // From calibration, setting correct values from ADC
//        qDebug() << user_temperature;
//        qDebug() << milk; // Prints for debugging
        memmove( y2, y2+1, (plotDataSize-1) * sizeof(double) );
        y2[plotDataSize-1] = plotvalue	;
        curve2.setSamples(x2, y2, plotDataSize); // Update plot
        plot.replot();
        Josh = 0; // Can be filled with new number
        // add the new input to the plot
       memmove( y1, y1+1, (plotDataSize-1) * sizeof(double) );
       y1[plotDataSize-1] = knobVal;
       curve1.setSamples(x1, y1, plotDataSize); // Update second plot line
       plot.replot();

    }

}


// this function can be used to change the gain of the A/D internal amplifier
void ConProdDialog::settemp(double usertemp)
{
    // for example purposes just change the amplitude of the generated input
    this->usertemp = usertemp;
}

// this function can be used to change the gain of the A/D internal amplifier
void ConProdDialog::setmilk(double usermilk)
{
    // for example purposes just change the amplitude of the generated input
    this->usermilk = usermilk;
}


