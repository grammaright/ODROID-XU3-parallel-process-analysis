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
       /* ARMSensorCurve = new QwtPlotCurve();
        MEMSensorCurve = new QwtPlotCurve();
        KFCSensorCurve = new QwtPlotCurve();
        G3DSensorCurve = new QwtPlotCurve();*/
       // displaySensorPlot();
}
analyzerwindow::~analyzerwindow()//소멸자로 동적할당 딜렉트
{
    takevalue->CloseINA231();
    delete ui;
}
/*void analyzerwindow::displaySensorPlot()//그래프선색,x축 y축
{
    ui->qwtPlotSensor->setAxisScale(QwtPlot::yLeft, 0, 5);
    ui->qwtPlotSensor->setAxisScale(QwtPlot::xBottom, 0, 100);
    ui->qwtPlotSensor->setAxisTitle(QwtPlot::xBottom, "sec");
    ui->qwtPlotSensor->setAxisTitle(QwtPlot::yLeft, "Watt");
    ui->qwtPlotSensor->setCanvasBackground(QBrush(QColor(0, 0, 0)));
    ui->qwtPlotSensor->setTitle("Watt Graph");
    ARMSensorCurve->attach(ui->qwtPlotSensor);//색을 넣어줌
    ARMSensorCurve->setPen(QColor(50, 160, 140));
    MEMSensorCurve->attach(ui->qwtPlotSensor);
    MEMSensorCurve->setPen(QColor(255, 0, 0));
    KFCSensorCurve->attach(ui->qwtPlotSensor);
    KFCSensorCurve->setPen(QColor(0, 255, 0));
    G3DSensorCurve->attach(ui->qwtPlotSensor);
    G3DSensorCurve->setPen(QColor(200, 160, 50));
}*/
/*void analyzerwindow::drawARMSensorCurve()//그래프그리기
{
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
}*/
/*void analyzerwindow::drawMEMSensorCurve()
{
    if (getNode->memuW > 0 && getNode->memuW < 10)
    {
        if (memPlotData.index < 99)
        {
            memPlotData.yData[memPlotData.index] = getNode->memuW;
            memPlotData.xData[memPlotData.index] = memPlotData.index;
            memPlotData.index++;
        }
        else
        {
            memPlotData.yData[99] = getNode->memuW;
            for (int i = 0; i < 100; i++)
            {
                memPlotData.yData[i] = memPlotData.yData[i + 1];
            }
        }
    }
    MEMSensorCurve->setSamples(memPlotData.xData, memPlotData.yData, memPlotData.index);
    ui->qwtPlotSensor->replot();
}
void analyzerwindow::drawKFCSensorCurve()
{
    if (getNode->kfcuW > 0 && getNode->kfcuW < 10)
    {
        if (kfcPlotData.index < 99)
        {
            kfcPlotData.yData[kfcPlotData.index] = getNode->kfcuW;
            ui->ARMuVlcd->display(a15Volt);
            ui->ARMuWlcd->display(a15Watt);
            kfcPlotData.xData[kfcPlotData.index] = kfcPlotData.index;
            kfcPlotData.index++;
        }
        else
        {
            kfcPlotData.yData[99] = getNode->kfcuW;
            for (int i = 0; i < 100; i++)
            {
                kfcPlotData.yData[i] = kfcPlotData.yData[i + 1];
            }
        }
    }
    KFCSensorCurve->setSamples(kfcPlotData.xData, kfcPlotData.yData, kfcPlotData.index);
    ui->qwtPlotSensor->replot();
}
void analyzerwindow::drawG3DSensorCurve()
{
    if (getNode->g3duW > 0 && getNode->g3duW < 10)
    {
        if (g3dPlotData.index < 99)
        {
            g3dPlotData.yData[g3dPlotData.index] = getNode->g3duW;
            g3dPlotData.xData[g3dPlotData.index] = g3dPlotData.index;
            g3dPlotData.index++;
        }
        else
        {
            g3dPlotData.yData[99] = getNode->g3duW;
            for (int i = 0; i < 100; i++)
            {
                g3dPlotData.yData[i] = g3dPlotData.yData[i + 1];
            }
        }
    }
    G3DSensorCurve->setSamples(g3dPlotData.xData, g3dPlotData.yData, g3dPlotData.index);
    ui->qwtPlotSensor->replot();
}*/

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
    ui->GPUFreqEdit->setText(takevalue->GetGPUCurFreq());
    ui->CPU0FreqEdit->setText(takevalue->GetCPUCurFreq(0));
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
    //drawARMSensorCurve();
    //drawMEMSensorCurve();
    //drawKFCSensorCurve();
    //drawG3DSensorCurve();
}
