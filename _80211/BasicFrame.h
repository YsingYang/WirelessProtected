#ifndef __BASICFRAME__
#define __BASICFRAME__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <vector>
#include "ieee80211.h"
#include "ieee80211_radiotap.h"

#define le16_to_cpu __le16_to_cpu

class CustomIe {
public:
    CustomIe();
    ~CustomIe();
    void setId(uint8_t id);
    void setLength(uint8_t length);
    void setData(std::vector<uint8_t>&);
    void setData(uint8_t* data, int length);
    void setData(std::string& data, int length);
    inline uint8_t getId() const ;
    inline uint8_t getLength() const ;
    inline std::vector<uint8_t> getData() const;
private:
    uint8_t id_;
    uint8_t len_;
    std::vector<uint8_t> data_;
};

uint8_t CustomIe::getId() const {
    return id_;
}

uint8_t CustomIe::getLength() const {
    return len_;
}

std::vector<uint8_t> CustomIe::getData() const{
    return data_;
}

class BasicFrame{
public:
    BasicFrame(uint32_t packetLength, uint32_t radiotapLength, u_char* data);
    ~BasicFrame();
    inline ieee80211_radiotap_header* getRadiotapHeader();
    inline uint32_t getPacketLength();
    inline uint32_t getRadiotapLength();
protected:
    uint32_t packetLength_;
    uint32_t radiotapLength_;
    ieee80211_radiotap_header*  radiotap_;
};

// mgmt frame
class SubBasicFrame : public BasicFrame{
public:
    SubBasicFrame(uint32_t packetLength, uint32_t radiotapLength, u_char* data);
    ~SubBasicFrame();
    inline bool isProbeRequest();
    inline ieee80211_mgmt* getMgmt();
    void setSeq(uint32_t);
    virtual void parse() = 0;
    virtual void resend() = 0;
    virtual void recombination() = 0;
    virtual void extractInformationElement() = 0;
    virtual void setSSID(std::string&) = 0;
    virtual void setHT() = 0;
    virtual void driverFunction();
    virtual void addIe(uint32_t id, int length, char* data) = 0;
protected:
    ieee80211_mgmt* mgmt;
};

class ProbeRequestFrame : public SubBasicFrame {
public:
    ProbeRequestFrame(uint32_t packetLength, uint32_t radiotapLength, u_char* data);
    ~ProbeRequestFrame();
    void setSSID(std::string SSID);
    void parse() override;
    void resend() override;
    void recombination() override;
    void extractInformationElement() override;
    void setSSID(std::string&) override;
    void setHT() override;
    void driverFunction() override;
    void addIe(uint32_t id, int length, char* data);
    bool checkVerdorSpecific(uint32_t id);
    inline std::vector<CustomIe*> getElements();

private:
    ieee80211_ie *ie;
    std::vector<CustomIe*> elements;
};

std::vector<CustomIe*> ProbeRequestFrame::getElements() {
    return elements;
}


bool SubBasicFrame::isProbeRequest(){
    return ieee80211_is_probe_req(mgmt->frame_control);
}

uint32_t BasicFrame::getPacketLength(){
    return packetLength_;
}

uint32_t BasicFrame::getRadiotapLength(){
    return radiotapLength_;
}

ieee80211_radiotap_header* BasicFrame::getRadiotapHeader() {
    return radiotap_;
}

ieee80211_mgmt* SubBasicFrame::getMgmt() {
    return mgmt;
}

#endif // __BASICFRAME__
