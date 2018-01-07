#include "Sender.h"

Sender::Sender():fd(-1){

}

Sender::~Sender(){

}

Sender::Sender::init() {
    broadcastSockFd_ = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(broadcastSockFd_ < 0) {
        perror
    }
}





