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
#include <memory>
#include <net/ethernet.h>
#include "../_80211/FrameFactory.h"


class Sender{
public:
    static Sender* getInstance();
    ~Sender();
    void init(char* );
    void recombination(ProbeRequestFrame* );
    void recombination(std::shared_ptr<SubBasicFrame>);
    void transmit();


private:
    Sender();
    inline void clean();
private:
    void copyDataToFakeFrame(char*, int length);
    static Sender* instance;
    int broadcastSockFd_;
    char fakeFrame_[1024];
    int counter;
};

void Sender::clean() { //将fakeFrame清空, counter 清0
    memset(fakeFrame_, 0, 1024);
    counter = 0;
}



#endif // __SENDER__
