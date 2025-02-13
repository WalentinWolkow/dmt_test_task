#ifndef CUSTOMTHREAD_H
#define CUSTOMTHREAD_H

#include <QThread>

class CustomThread : public QThread
{
//    Q_OBJECT
public:
    explicit CustomThread(void (&func)(), int timeout = 1, QObject *parent = nullptr);
    ~CustomThread();

protected:
    void run() final;

private:
    void (&stepFunc)();
    int pipeId[2];
    int mTimeout;

//signals:

};

#endif // CUSTOMTHREAD_H
