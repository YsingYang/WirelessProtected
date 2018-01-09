#include "Sender.h"

Sender* Sender::instance = nullptr;

Sender::Sender() : broadcastSockFd_(-1){

}

Sender* Sender::getInstance() {
    if(instance == nullptr) {
        instance = new Sender();
    }
    return instance;
}

Sender::~Sender(){

}

void Sender::Sender::init(char* interface) {
    broadcastSockFd_ = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(broadcastSockFd_ < 0) {
        perror("Create raw socket error");
    }
    struct ifreq interfaceRequest;
    memset((void*)&interfaceRequest, 0, sizeof(struct ifreq));
    strncpy(interfaceRequest.ifr_name, interface, strlen(interface)+1); //?????
    if(ioctl(broadcastSockFd_, SIOGIFINDEX, &interfaceRequest) < 0) {
        perror("SIOGIFINDEX Error");
    }

    struct sockaddr_ll sockAddr;
    memset((void*)&sockAddr, 0, sizeof(sockaddr_ll));
    sockAddr.sll_family = AF_PACKET;
    sockAddr.sll_ifindex = interfaceRequest.ifr_ifindex;
    sockAddr.sll_protocol = htons(ETH_P_ALL);
    if(bind(broadcastSockFd_, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) < 0){
        perror("Raw socket binding error");
    }
    struct packet_mreq promiseSet;
    memset((void*)&promiseSet, 0, sizeof(promiseSet));
    promiseSet.mr_ifindex = sockAddr.sll_ifindex;
    promiseSet.mr_type = PACKET_MR_PROMISC;
    if(setsockopt(broadcastSockFd_, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &promiseSet, sizeof(promiseSet)) < 0) {
        perror("setsocketopt (promise ) failed");
    }
}

void Sender::recombination(ProbeRequestFrame* pr) {
    //直接在原帧上进行修改, 再copy到char数组中
    /******************************

        这里注意一个问题, le16_to_cpu与原来得到的是一样的结果,  所以应该避免.

    ******************************/

    int seq = le16_to_cpu(pr->getMgmt()->seq_ctrl) >> 4;
    seq = ((seq + 1) << 4);
    std::cout<<seq<<std::endl;
    std::cout<<htons(seq)<<std::endl;

}






