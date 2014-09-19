#include "analyzerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    analyzerWindow w;
    w.show();

    return a.exec();
}
