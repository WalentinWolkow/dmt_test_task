#ifndef CUSTOMTHREAD_H
#define CUSTOMTHREAD_H

#include "custombasethread.h"
#include <custommodel.h>

#define THREAD_ONE_TIMEOUT  3

class CustomThreadOne : public CustomBaseThread
{
public:
    explicit CustomThreadOne(CustomModel *model, QObject *parent = nullptr)
        : CustomBaseThread(THREAD_ONE_TIMEOUT, parent)
        , mModel(model)
    {
    }

    ~CustomThreadOne()
    {
    }


    void stepFunction() final;

private:
    CustomModel *mModel;
};


#define THREAD_TWO_TIMEOUT  5

class CustomThreadTwo : public CustomBaseThread
{
public:
    explicit CustomThreadTwo(CustomModel *model, QObject *parent = nullptr)
        : CustomBaseThread(THREAD_TWO_TIMEOUT, parent)
        , mModel(model)
    {
    }

    ~CustomThreadTwo()
    {
    }


    void stepFunction() final;

private:
    CustomModel *mModel;
};

#endif  // CUSTOMTHREAD_H
