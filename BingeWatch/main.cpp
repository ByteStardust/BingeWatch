#include "BingeWatch.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BingeWatch w;
    w.show();
    return a.exec();
}
