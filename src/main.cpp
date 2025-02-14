#include <QApplication>

#include <mainwidget.h>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWidget *mw = new MainWidget;
    mw->show();

    int res = app.exec();

    delete mw;

    return res;
}
