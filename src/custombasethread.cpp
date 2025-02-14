#include "custombasethread.h"

#include <iostream>

#include <unistd.h>
#include <poll.h>

CustomBaseThread::CustomBaseThread(int timeout, QObject *parent)
    : QThread(parent)
    , mTimeout(timeout * 1000)
{
    if (pipe(pipeId) != -1)
    {
        start();
        return;
    }

    pipeId[0] = pipeId[1] = -1;
}

CustomBaseThread::~CustomBaseThread()
{
    if (pipeId[1] != -1)
    {
        write(pipeId[1], "Q", sizeof(char));
        wait();

        ::close(pipeId[1]);
    }

    if (pipeId[0] != -1)
        ::close(pipeId[0]);
}


void CustomBaseThread::run()
{
    struct pollfd pollfd;
    pollfd.fd = pipeId[0];
    pollfd.events = POLLIN;

    for ( ; ; )
    {
        stepFunction();

        int res = poll(&pollfd, 1, mTimeout);
        if (res == 0)
            continue;

        if (res == -1)
        {
            std::cerr << "poll() error!\n";
            break;
        }

        if (pollfd.revents & POLLIN)
        {
            char c;
            read(pollfd.fd, &c, sizeof(char));

            if (c == 'Q' || c == 'q')
                break;
        }
    }
}
