#ifndef __PCAPMANAGER_H

#include <stdio.h>
#include <pcap.h>
#include <iostream>
#include <functional>
#include "../_80211/ieee80211.h"

/*******************************

        需要单例?

********************************/

class PcapManager {
private:
    //typedef std::function<void(u_char* user, const struct pcap_pkthdr* packetHeader, const u_char* packetData)> pcapCallbackType ;
    typedef void (*pcapCallbackType) (u_char* user, const struct pcap_pkthdr* packetHeader, const u_char* packetData);
public:
    PcapManager(std::string netCard);
    void funLoop(int time);   //回调函数执行次数, 若为-1则无限循环
    void setLoopFunction(pcapCallbackType);

private:
    std::string netcardName_;
    char errbuf_[1024];
    pcap_t* pcapHandler_;
    pcapCallbackType loopFunction_;
};


#endif // __PCAPMANAGER_H
