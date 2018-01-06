#include "./PcapManager.h"

PcapManager::PcapManager(std::string netcard) :
    netcardName_(netcard),
    pcapHandler_(nullptr){
        pcapHandler_ = pcap_open_live(const_cast<char* >(netcardName_.c_str()), 65535, 1, 0, errbuf_);
        if(pcapHandler_ == nullptr) {
            printf("pcapOpen Error\n");
            exit(0);
        }
}


void PcapManager::setLoopFunction(PcapManager::pcapCallbackType callbackFunction){
    loopFunction_ = callbackFunction;
}

void PcapManager::funLoop(int time){
    pcap_loop(pcapHandler_, time,  loopFunction_, (u_char*) "Ysing");
}
