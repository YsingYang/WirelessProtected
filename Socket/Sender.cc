#include "Sender.h"

/********************************

    继续Sender的中transmit代码编写

***********************************/


Sender* Sender::instance = nullptr;

Sender::Sender() : broadcastSockFd_(-1), counter(0), isInit_(false){

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
    isInit_ = true;
}

void Sender::recombination(ProbeRequestFrame* pr){

}

void Sender::recombination(std::shared_ptr<SubBasicFrame> pr) {
    /******************************

        这里注意一个问题, le16_to_cpu与原来得到的是一样的结果,  所以应该避免.

    ******************************/
    int seq = le16_to_cpu(pr->getMgmt()->seq_ctrl) >> 4;
    seq = ((seq + 1) << 4);
    pr->setSeq(seq);
    std::string ssid = "Test2";
    pr->setSSID(ssid);
}

void Sender::transmit(std::shared_ptr<SubBasicFrame> pr) {
    //先将帧拷贝到字符数组中
    clean();
    copyDataToFakeFrame((char*)(pr->getRadiotapHeader()), pr->getRadiotapLength());
    copyDataToFakeFrame((char*)(pr->getMgmt()), 24); //这里直接写mgmt为24好像不太好.
    std::shared_ptr<ProbeRequestFrame> probe = std::dynamic_pointer_cast<ProbeRequestFrame>(pr);
    std::vector<CustomIe*> elements = probe->getElements();
    for(uint32_t i = 0; i < elements.size(); ++i) {
        copyInfomationElements(elements[i]);
        std::cout<<elements[i]->getId()<< "    "<<elements[i]->getLength()<<"   "<<std::endl;
    }
    /*if(write(broadcastSockFd_, fakeFrame_, counter) < 0) {
        perror("send 80211 packet error");
    }*/
}

void Sender::copyDataToFakeFrame(char* data, int length) {
    memcpy(fakeFrame_ + counter, data, length);
    counter += length;
}

void Sender::copyInfomationElements(CustomIe* ie) {
    fakeFrame_[counter] = ie->getId();
    counter += 1;
    fakeFrame_[counter] = ie->getLength();
    counter += 1;
    memcpy(fakeFrame_ + counter, &(ie->getData()[0]), ie->getLength());
    counter += ie->getLength();
}






