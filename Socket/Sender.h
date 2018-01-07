#ifndef __SENDER__
#define __SENDER__

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <net/if.h>


class Sender{
public:
    Sender();
    void init();
    ~Sender();

private:
    int broadcastSockFd_;
    char fakeFrame_[1024];
};


#endif // __SENDER__
