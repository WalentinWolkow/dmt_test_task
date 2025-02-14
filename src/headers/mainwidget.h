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

    CustomModel *mModel;

private slots:
    void slotCheckBox(bool);
    void slotLineEdit(QString);
};
#endif // MAINWIDGET_H
