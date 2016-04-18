#include "conproddialog.h"
#include <QApplication>
#include "conproddialog.h"
#include "common.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConProdDialog w; // Create an instance where the whole program will run from

    w.showMaximized();
    w.startTimer(1); // Start the application

    return a.exec();
}
