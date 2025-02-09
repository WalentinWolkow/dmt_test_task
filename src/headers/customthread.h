#ifndef CUSTOMTHREAD_H
#define CUSTOMTHREAD_H

#include <QThread>

class CustomThread : public QThread
{
//    Q_OBJECT
public:
    explicit CustomThread(void (&)(), int = 1, QObject * = nullptr);
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
