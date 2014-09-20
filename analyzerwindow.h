#ifndef ANALYZERWINDOW_H
#define ANALYZERWINDOW_H

#include <QWidget>
//#include <qwt_plot.h>
//#include <qwt_plot_curve.h>
class Takevalue;
namespace Ui {//namespace 로Ui를 설정한것이다.
class analyzerWindow;
}
typedef struct plotdata {//이름없는 구조체로 typedef 를써주고,
double xData[100];//그래프의x좌표와y좌표
double yData[100];
int index;
float Watt;
} plotdata;
class analyzerwindow : public QWidget
{
Q_OBJECT//Q_OBJECT 가제공하는 서비스 (신호, 슬롯, 메타 오브젝트 정보)를사용하기위해 클래스에선언한다.
public:
explicit analyzerwindow(QWidget *parent = 0);
~analyzerwindow();
private:
Ui::analyzerWindow *ui;
Takevalue *takevalue;
/*QwtPlotCurve *ARMSensorCurve;//여러곡선들을 표현하기위해QwtPlotCurve로지정해준다.
QwtPlotCurve *MEMSensorCurve;
QwtPlotCurve *KFCSensorCurve;
QwtPlotCurve *G3DSensorCurve;
QwtPlot *qwtPlotSensor;*/
plotdata armPlotData;//센세들에게서 데이터들을받아오기위해 선언한다.
plotdata memPlotData;
plotdata kfcPlotData;
plotdata g3dPlotData;
QString a15Volt, a15Ampere, a15Watt;//받아온 데이터들을 분류해줘서 저장할string형변수를여러개 선언해준다.
QString a7Volt, a7Ampere, a7Watt;
QString gpuVolt, gpuAmpere, gpuWatt;
QString memVolt, memAmpere, memWatt;
void DisplaySensor(void);
void float2string(void);
void displaySensorPlot(void);
void drawARMSensorCurve(void);
void drawMEMSensorCurve(void);
void drawKFCSensorCurve(void);
void drawG3DSensorCurve(void);
void displayCpuFrequency(void);
void displayCpuUsage(void);
private slots:
void update();//버튼을누를때 인터럽트될함수
};

#endif // ANALYZERWINDOW_H
