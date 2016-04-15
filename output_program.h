#ifndef OUTPUT_PROGRAM_H
#define OUTPUT_PROGRAM_H
#include <QtCore>
#include <QThread>
#include <QTime>

class output_program : public QThread
{
    Q_OBJECT
public:
    explicit output_program(QObject *parent = 0);
    void run();

signals:


public slots:
};

#endif // OUTPUT_PROGRAM_H
