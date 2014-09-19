#include "analyzerwindow.h"
#include "ui_analyzerwindow.h"
#include <QGraphicsView>
analyzerWindow::analyzerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::analyzerWindow)
{
    ui->setupUi(this);

}

analyzerWindow::~analyzerWindow()
{
    delete ui;
}
