#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class CustomModel;

namespace Ui {
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

    CustomModel *model;
};
#endif // MAINWIDGET_H
