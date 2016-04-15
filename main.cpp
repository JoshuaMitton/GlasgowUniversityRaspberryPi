#include "conproddialog.h"
#include <QApplication>
#include "conproddialog.h"
#include "common.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConProdDialog w;

    w.showMaximized();
    w.startTimer(1);

    return a.exec();
}
