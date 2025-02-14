#ifndef CUSTOMBASETHREAD_H
#define CUSTOMBASETHREAD_H

#include <QThread>

class CustomBaseThread : public QThread
{
//    Q_OBJECT
public:
    explicit CustomBaseThread(int timeout = 1, QObject *parent = nullptr);
    ~CustomBaseThread();

    virtual void stepFunction() = 0;

protected:
    void run() final;

private:
    int pipeId[2];
    int mTimeout;

//signals:

};

#endif // CUSTOMBASETHREAD_H
