#include "./BasicFrame.h"
/************

CustomIe应该存在什么容器里.
如何修改data域

*************/

CustomIe::CustomIe(): id_(-1), len_(-1){}

CustomIe::~CustomIe(){
}

void CustomIe::setId(uint8_t id) {
    id_ = id;
}

void CustomIe::setLength(uint8_t length) {
    len_ = length;
}

void CustomIe::setData(std::vector<uint8_t>& data) {
    int length = data.size();
    data_.resize(length);
    memcpy(&data_[0], &data[0], length);
}

void CustomIe::setData(uint8_t* data, int length) {
    data_.resize(length);
    memcpy(&data_[0], data, length);
}

void CustomIe::setData(std::string& data, int length) {
    data_.resize(length);
    memcpy(&data_[0], &data[0], length);
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

    /*********************************
        析构掉element中每一个元素的部分
    **********************************/
ProbeRequestFrame::~ProbeRequestFrame(){
    for(uint32_t i = 0; i < elements.size(); ++i) {
        delete elements[i];
    }
}

void SubBasicFrame::setSeq(uint32_t seq) {
    mgmt->seq_ctrl = seq << 4;
}

void SubBasicFrame::driverFunction(){

}


void ProbeRequestFrame::extractInformationElement() {
    int remainLength = packetLength_ - radiotapLength_ - 24;
    ieee80211_ie* tempIe = ie;
    while(remainLength > FCS_LEN) {
        int currentLength = tempIe->len;
        CustomIe* customIe = new CustomIe();
        customIe->setId(tempIe->id);
        customIe->setLength(tempIe->len);
        customIe->setData(tempIe->data, tempIe->len);
        elements.emplace_back(customIe);
        remainLength = remainLength - currentLength - 2;
        tempIe = (ieee80211_ie*) ((char*)(tempIe) + currentLength + 2);
    }
}

void ProbeRequestFrame::setSSID(std::string& SSID) {
    bool flag = false;
    int newLength = SSID.size();
    for(uint32_t i = 0; i < elements.size(); ++i) {
        if(flag){
            break;
        }
        if(elements[i]->getId() == WLAN_EID_SSID) {
            elements[i]->setData(SSID, newLength);
            elements[i]->setLength(newLength); //不要忘记修改了ssid后还需要修改长度
            flag = true;
        }
    }
}

void ProbeRequestFrame::setHT(){
}

void ProbeRequestFrame::driverFunction() {

}

bool ProbeRequestFrame::checkVerdorSpecific(uint32_t id, uint32_t*) {

}

void ProbeRequestFrame::parse() {
    int remainLength = packetLength_ - radiotapLength_ - 24; //减取radioTap与非ie部分
    ieee80211_ie* tempIe = ie;
    while(remainLength > FCS_LEN) {
        switch(tempIe-> id) {
            case WLAN_EID_SSID: {
                int ssidLength = tempIe->len;
                std::string ssid = std::string((char*)(tempIe->data), ssidLength);
                break;
            }
            case WLAN_EID_HT_CAPABILITY: {
                ieee80211_ht_cap* htCap = (ieee80211_ht_cap*)  (tempIe->data);
                int htInfo = le16_to_cpu(htCap->cap_info);
                break;
            }
        }
        int currentLength = tempIe->len;
        tempIe = (ieee80211_ie*)((char*)(tempIe) + currentLength + 2);
        remainLength  = remainLength - currentLength - 2 ;
    }
}

void ProbeRequestFrame::addIe(uint32_t id, int length, char* data) {
    CustomIe* ie = new CustomIe();
    ie->setId(id);
    ie->setLength(length);
    ie->setData((uint8_t*)(data), length);
}

void ProbeRequestFrame::recombination() {
}

void ProbeRequestFrame::resend(){

}
