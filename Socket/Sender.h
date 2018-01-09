#ifndef __SENDER__
#define __SENDER__

#include <stdio.h>
#include <arpa/inet.h>  //htons
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include<linux/if_packet.h>
#include <sys/ioctl.h> //ioctl
#include <net/if.h>
#include <linux/if_ether.h>
#include <net/ethernet.h>
#include "../_80211/FrameFactory.h"


class Sender{
public:
    static Sender* getInstance();
    ~Sender();
    void init(char* );
    void recombination(ProbeRequestFrame* );


private:
    Sender();
    static Sender* instance;
    int broadcastSockFd_;
    char fakeFrame_[1024];
};



#endif // __SENDER__
