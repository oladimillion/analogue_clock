#include "clock.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Clock c;
    c.show();

    return a.exec();
}
