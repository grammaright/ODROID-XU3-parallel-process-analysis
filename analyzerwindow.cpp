#include "analyzerwindow.h"
#include "ui_analyzerwindow.h"
#include "takevalue.h"
#include <QTimer>
#include <QDebug>
#include <QPalette>
analyzerwindow::analyzerwindow(QWidget *parent) :
QWidget(parent),
ui(new Ui::analyzerWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));//몇초마다 갱신한다.
    timer->start(1000);//1초마다
    takevalue = new Takevalue();
    displayCpuFrequency();
    if (takevalue->OpenINA231())
        qDebug() << "OpenINA231 error";
    else
        takevalue->GetINA231();
        armPlotData.index = 0;
        memPlotData.index = 0;
        kfcPlotData.index = 0;
        g3dPlotData.index = 0;
        a15Volt = a15Ampere = a15Watt = "";
        a7Volt = a7Ampere = a7Watt = "";
        gpuVolt = gpuAmpere = gpuWatt = "";
        memVolt = memAmpere = memWatt = "";
        /*
        ARMSensorCurve = new QwtPlotCurve();
        MEMSensorCurve = new QwtPlotCurve();
        KFCSensorCurve = new QwtPlotCurve();
        G3DSensorCurve = new QwtPlotCurve();

        ui->
        displaySensorPlot();
        */
        displaySensorPlot();
}
analyzerwindow::~analyzerwindow()//소멸자로 동적할당 딜렉트
{
    takevalue->CloseINA231();
    delete ui;
}
void analyzerwindow::displaySensorPlot()//그래프선색,x축 y축
{
    ui->qwtPlotSensor->addGraph();
    ui->qwtPlotSensor->addGraph();
    ui->qwtPlotSensor->addGraph();
    ui->qwtPlotSensor->xAxis->setRange(0.f,100.f);
    ui->qwtPlotSensor->yAxis->setRange(0.f,2.f);
    ui->qwtPlotSensor->graph(2)->setPen(QPen(Qt::red));
    ui->qwtPlotSensor->graph(1)->setPen(QPen(Qt::green));

}
void analyzerwindow::drawARMSensorCurve()//그래프그리기
{
    /*
    if (getNode->armuW > 0 && getNode->armuW < 10)
    {
        if (armPlotData.index < 99)
        {
            armPlotData.yData[armPlotData.index] = getNode->armuW;
            armPlotData.xData[armPlotData.index] = armPlotData.index;
            armPlotData.index++;
        }
            else
            {
                armPlotData.yData[99] = getNode->armuW;
                for (int i = 0; i < 100; i++)
                {
                     armPlotData.yData[i] = armPlotData.yData[i + 1];
                }
            }
        }
    ARMSensorCurve->setSamples(armPlotData.xData, armPlotData.yData, armPlotData.index);
    ui->qwtPlotSensor->replot();
    */
}
void analyzerwindow::drawMEMSensorCurve()
{
    if (takevalue->memuW > 0 && takevalue->memuW < 10)
    {
            y[0].push_back(takevalue->memuW*5);
            x[0].push_back(memPlotData.index);
            if( memPlotData.index > 99 )
                y[0].pop_front();
            else
                memPlotData.index++;
    }
    ui->qwtPlotSensor->graph(0)->setData(x[0], y[0]);
    ui->qwtPlotSensor->replot();

}
void analyzerwindow::drawKFCSensorCurve()
{
    if (takevalue->memuA > 0 && takevalue->memuA < 10)
    {
            y[1].push_back(takevalue->memuA);
            x[1].push_back(kfcPlotData.index);
            if( kfcPlotData.index > 99 )
                y[1].pop_front();
            else
                kfcPlotData.index++;
    }
    ui->qwtPlotSensor->graph(1)->setData(x[1], y[1]);
    ui->qwtPlotSensor->replot();
}
void analyzerwindow::drawG3DSensorCurve()
{
    if (takevalue->memuV > 0 && takevalue->memuV < 10)
    {
            y[2].push_back(takevalue->memuV);
            x[2].push_back(g3dPlotData.index);
            if( g3dPlotData.index > 99 )
                y[2].pop_front();
            else
                g3dPlotData.index++;

    }
    ui->qwtPlotSensor->graph(2)->setData(x[2], y[2]);
    ui->qwtPlotSensor->replot();
}

void analyzerwindow::DisplaySensor()//cpu값넣는 곳세팅
{
    takevalue->GetINA231();
    float2string();
    ui->ARMuVlcd->setPalette(QColor(100, 100, 100));
    ui->ARMuAlcd->display(a15Ampere);
    ui->ARMuAlcd->setPalette(QColor(100, 100, 100));
    ui->ARMuWlcd->setPalette(QColor(100, 100, 100));
    ui->ARMuVlcd->display(a15Volt);
    ui->ARMuWlcd->display(a15Watt);
    ui->KFCuVlcd->setPalette(QColor(100, 100, 100));
    ui->KFCuAlcd->setPalette(QColor(100, 100, 100));
    ui->KFCuWlcd->setPalette(QColor(100, 100, 100));
    ui->KFCuVlcd->display(a7Volt);
    ui->KFCuAlcd->display(a7Ampere);
    ui->KFCuWlcd->display(a7Watt);
    ui->G3DuVlcd->setPalette(QColor(100, 100, 100));
    ui->G3DuAlcd->setPalette(QColor(100, 100, 100));
    ui->G3DuWlcd->setPalette(QColor(100, 100, 100));
    ui->G3DuVlcd->display(gpuVolt);
    ui->G3DuAlcd->display(gpuAmpere);
    ui->G3DuWlcd->display(gpuWatt);
    ui->MEMuVlcd->setPalette(QColor(100, 100, 100));
    ui->MEMuAlcd->setPalette(QColor(100, 100, 100));
    ui->MEMuWlcd->setPalette(QColor(100, 100, 100));
    ui->MEMuVlcd->display(memVolt);
    ui->MEMuAlcd->display(memAmpere);
    ui->MEMuWlcd->display(memWatt);
}
void analyzerwindow::float2string()//값을 출력한다.
{
    a15Volt.sprintf("%.3f", takevalue->armuV);
    a15Ampere.sprintf("%.3f", takevalue->armuA);
    a15Watt.sprintf("%.3f", takevalue->armuW);
    a7Volt.sprintf("%.3f", takevalue->kfcuV);
    a7Ampere.sprintf("%.3f", takevalue->kfcuA);
    a7Watt.sprintf("%.3f", takevalue->kfcuW);
    gpuVolt.sprintf("%.3f", takevalue->g3duV);
    gpuAmpere.sprintf("%.3f", takevalue->g3duA);
    gpuWatt.sprintf("%.3f", takevalue->g3duW);
    memVolt.sprintf("%.3f", takevalue->memuV);
    memAmpere.sprintf("%.3f", takevalue->memuA);
    memWatt.sprintf("%.3f", takevalue->memuW);
}
void analyzerwindow::displayCpuFrequency()
{
    QString temp = takevalue->GetCPUCurFreq(0);
    ui->GPUFreqEdit->setText(takevalue->GetGPUCurFreq());
    ui->CPU0FreqEdit->setText(temp);
    ui->CPU1FreqEdit->setText(takevalue->GetCPUCurFreq(1));
    ui->CPU2FreqEdit->setText(takevalue->GetCPUCurFreq(2));
    ui->CPU3FreqEdit->setText(takevalue->GetCPUCurFreq(3));
    ui->CPU4FreqEdit->setText(takevalue->GetCPUCurFreq(4));
    ui->CPU5FreqEdit->setText(takevalue->GetCPUCurFreq(5));
    ui->CPU6FreqEdit->setText(takevalue->GetCPUCurFreq(6));
    ui->CPU7FreqEdit->setText(takevalue->GetCPUCurFreq(7));
    ui->CPU4TempEdit->setText(takevalue->GetCPUTemp(0));
    ui->CPU5TempEdit->setText(takevalue->GetCPUTemp(1));
    ui->CPU6TempEdit->setText(takevalue->GetCPUTemp(2));
    ui->CPU7TempEdit->setText(takevalue->GetCPUTemp(3));
    ui->GPUTempEdit->setText(takevalue->GetCPUTemp(4));
}
void analyzerwindow::update()//업데이트
{
    displayCpuFrequency();
    DisplaySensor();
    drawARMSensorCurve();
    drawMEMSensorCurve();
    drawKFCSensorCurve();
    drawG3DSensorCurve();
    displayCpuUsage();
}

void analyzerwindow::displayCpuUsage()
{
    takevalue->GetCPUUsage();
    ui->CPU0UsageEdit->setText(QString::number(takevalue->usage[0]));
    ui->CPU1UsageEdit->setText(QString::number(takevalue->usage[1]));
    ui->CPU2UsageEdit->setText(QString::number(takevalue->usage[2]));
    ui->CPU3UsageEdit->setText(QString::number(takevalue->usage[3]));
    ui->CPU4UsageEdit->setText(QString::number(takevalue->usage[4]));
    ui->CPU5UsageEdit->setText(QString::number(takevalue->usage[5]));
    ui->CPU6UsageEdit->setText(QString::number(takevalue->usage[6]));
    ui->CPU7UsageEdit->setText(QString::number(takevalue->usage[7]));
}

