#include "OccQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OccQt w;
    w.show();
    return a.exec();
}
