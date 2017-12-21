#include "./pcap/PcapManager.h"

void loopfunction(u_char* user, const struct pcap_pkthdr* packetHeader, const u_char* packetData) {

}

int main() {
    PcapManager* pm = new PcapManager("wlan0");
    pm->setLoopFunction(loopfunction);
    pm->funLoop(-1);
}
