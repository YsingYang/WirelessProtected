#include "./BasicFrame.h"


BasicFrame::BasicFrame(uint32_t packetLength, uint32_t radiotapLength, u_char* data)
    : packetLength_(packetLength), radiotapLength_(radiotapLength), radiotap_((ieee80211_radiotap_header*)(data)){

}

SubBasicFrame::SubBasicFrame(uint32_t packetLength, uint32_t radiotapLength, u_char* data)
    : BasicFrame(packetLength, radiotapLength, data), mgmt((ieee80211_mgmt*)(radiotap_ + radiotapLength_)) {
    }

ProbeRequestFrame::ProbeRequestFrame(uint32_t packetLength, uint32_t radiotapLength, u_char* data)
    : SubBasicFrame(packetLength, radiotapLength, data),  ie((struct ieee80211_ie*)mgmt->u.beacon.variable){
    }

BasicFrame::~BasicFrame() {}

SubBasicFrame::~SubBasicFrame() {}

ProbeRequestFrame::~ProbeRequestFrame() {}

void ProbeRequestFrame::parse() {
    std::cout<<isProbeRequest()<<std::endl;
}
