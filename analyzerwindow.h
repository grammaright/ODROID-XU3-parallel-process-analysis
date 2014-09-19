#ifndef ANALYZERWINDOW_H
#define ANALYZERWINDOW_H

#include <QWidget>

namespace Ui {
class analyzerWindow;
}

class analyzerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit analyzerWindow(QWidget *parent = 0);
    ~analyzerWindow();

private:
    Ui::analyzerWindow *ui;
};

#endif // ANALYZERWINDOW_H
