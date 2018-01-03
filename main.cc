#include <memory>

#include "./pcap/PcapManager.h"
#include "./_80211/BasicFrame.h"
#include "./_80211/FrameFactory.h"

#define le16_to_cpu __le16_to_cpu


void loopfunction(u_char* user, const struct pcap_pkthdr* packetHeader, const u_char* packetData) {
    uint32_t packetLength = packetHeader->caplen;
    struct ieee80211_radiotap_header* rtHeader = (struct ieee80211_radiotap_header*)(packetData);
    uint32_t rtLength = le16_to_cpu(rtHeader->it_len);
    if(rtLength > packetLength){
        printf("exceeding packet size\n");
        return;
    }

    std::shared_ptr<SubBasicFrame> probeRequest = createFrame(packetLength, rtLength, const_cast<u_char*>(packetData + rtLength));
    if(probeRequest != nullptr) {
        probeRequest ->parse();
    }
}

int main() {
    PcapManager* pm = new PcapManager("wlan0");
    pm->setLoopFunction(loopfunction);
    pm->funLoop(-1);
}
