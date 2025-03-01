#ifndef CUSTOMBASETHREAD_H
#define CUSTOMBASETHREAD_H

#include <QThread>

class QMutex;

class CustomBaseThread : public QThread
{
public:
    explicit CustomBaseThread(int timeout = 1, QObject *parent = nullptr);
    ~CustomBaseThread();

    static QMutex * getMutex();

    virtual void stepFunction() = 0;

protected:
    void run() final;

private:
    int pipeId[2];
    int mTimeout;
};

#endif // CUSTOMBASETHREAD_H
