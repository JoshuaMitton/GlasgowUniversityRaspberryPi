#ifndef CONPRODDIALOG_H
#define CONPRODDIALOG_H

#include <QDialog>
#include "consumer.h"
#include "producer.h"
#include "output_program.h"
#include <QSemaphore>
#include <qwt/qwt_slider.h>
#include <qwt/qwt_abstract_slider.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <QtCore>
#include <QtGui>
#include <QSlider>
#include <QBoxLayout>
// Include all QT plotting 


namespace Ui {
class ConProdDialog;
}

class ConProdDialog : public QWidget
{
    Q_OBJECT

public:
    ConProdDialog();

//    ~ConProdDialog();
    
    void timerEvent( QTimerEvent * ); // timer event

//    explicit ConProdDialog(QWidget *parent = 0);
//    ~ConProdDialog();

public slots:
    void settemp(double usertemp); // gain functions
    void setmilk(double usermilk);

private slots:


private:
//    Ui::ConProdDialog *ui;
    Producer *mProducer;
    Consumer *mConsumer; // ring buffer input output
    output_program *moutput_program;
    // graphical elements from the Qwt library
      QwtKnob      knob;
      QwtKnob      knob2;
      QwtPlot      plot;
      QwtPlotCurve curve1;
      QwtPlotCurve curve2;
      QwtSlider *slider;

      // layout elements from Qt itself
      QVBoxLayout  vLayout;  // vertical layout
      QHBoxLayout  hLayout;  // horizontal layout

      static const int plotDataSize = 100;

      // data arrays for the plot
      double x1[plotDataSize];
      double y1[plotDataSize];
      double x2[plotDataSize];
      double y2[plotDataSize];

      // user values
      double usertemp;
      double actualtemp;
      double usermilk;

      double knobVal;
      double knob2Val;
};

#endif // CONPRODDIALOG_H
