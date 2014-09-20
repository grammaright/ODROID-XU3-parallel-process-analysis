#include "analyzerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    analyzerwindow w;
    w.show();

    return a.exec();
}
