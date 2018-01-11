#include "./BasicFrame.h"
/************

CustomIe应该存在什么容器里.
如何修改data域

*************/

CustomIe::CustomIe(): id(-1), len(-1){}

void CustomIe::setId(uint8_t id) {
    id_ = id;
}

void CustomIe::setLength(uint8_t length) {
    len_ = length;
}

void CustomIe::setData(std::vector<uint8_t> data) {
    data_.emplace_back(data);
}

BasicFrame::BasicFrame(uint32_t packetLength, uint32_t radiotapLength, u_char* data)
    : packetLength_(packetLength), radiotapLength_(radiotapLength), radiotap_((ieee80211_radiotap_header*)(data)){

}

SubBasicFrame::SubBasicFrame(uint32_t packetLength, uint32_t radiotapLength, u_char* data)
    : BasicFrame(packetLength, radiotapLength, data), mgmt((ieee80211_mgmt*)(data + radiotapLength_)) {
    }

ProbeRequestFrame::ProbeRequestFrame(uint32_t packetLength, uint32_t radiotapLength, u_char* data)
    : SubBasicFrame(packetLength, radiotapLength, data),  ie((struct ieee80211_ie*)(mgmt->u.probe_req.variable)){
    }

BasicFrame::~BasicFrame() {}

SubBasicFrame::~SubBasicFrame() {}

ProbeRequestFrame::~ProbeRequestFrame() {
    /*********************************
        析构掉element中每一个元素的部分
    **********************************/
    for(int i = 0; i < elements.size(); ++i) {
        delete elements[i];
    }
}

void SubBasicFrame::setSeq(uint32_t seq) {
    mgmt->seq_ctrl = htons(seq << 4);
}

void ProbeRequestFrame::extractInformationElement() {
    int remainLength = packetLength_ - radiotapLength_ - 24;
    while(remainLength > FCS_LEN) {
        int currentLength = ie->len;
        CustomIe* customIe = new CustomIe();
        customIe

        remainLength -= ie->len - 2;
        ie = (ieee80211_ie*) ((char*)(ie) + currentLength + 2);
    }
}

void ProbeRequestFrame::setSSID(std::string SSID) {

}

void ProbeRequestFrame::parse() {
    std::cout<<"packetLength :  " << packetLength_ <<"   radiotapLength : " <<radiotapLength_<<std::endl;
    int remainLength = packetLength_ - radiotapLength_ - 24; //减取radioTap与非ie部分
    while(remainLenght > FCS_LEN) {
        switch(ie -> id) {
            case WLAN_EID_SSID: {
                int ssidLength = ie->len;
                std::string ssid = std::string((char*)(ie->data), ssidLength);
                std::cout<<"ssidLenght  : "<<ssidLength<<" ssid  : " +  ssid<<std::endl;
                break;
            }
            case WLAN_EID_HT_CAPABILITY: {
                ieee80211_ht_cap* htCap = (ieee80211_ht_cap*)  (ie->data);
                int htInfo = le16_to_cpu(htCap->cap_info);
                std::cout<<"ht  : " <<htInfo<<std::endl;
                break;
            }
        }
        int currentLength = ie->len;
        ie = (ieee80211_ie*)((char*)(ie) + currentLength + 2);
        remainLenght  -= currentLength;
    }
}

void ProbeRequestFrame::recombination() {
    u_char FakeBeaconFrame[1024];
}

void ProbeRequestFrame::resend(){

}
