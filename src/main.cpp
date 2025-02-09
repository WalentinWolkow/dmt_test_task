#include <QApplication>

#include <mainwidget.h>
#include <customthread.h>
#include <threadfuncs.h>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWidget *mw = new MainWidget;

    new CustomThread(functionOne, 3, mw);
    new CustomThread(functionTwo, 5, mw);

    mw->show();

    int res = app.exec();

    delete mw;

    return res;
}
