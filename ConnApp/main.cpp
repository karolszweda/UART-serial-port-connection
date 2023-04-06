#include "connwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnWindow w;
    w.show();
    return a.exec();
}
