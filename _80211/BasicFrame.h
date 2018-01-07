#ifndef __BASICFRAME__
#define __BASICFRAME__

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/if_ether.h>

#include "ieee80211.h"
#include "ieee80211_radiotap.h"

#define le16_to_cpu __le16_to_cpu

class BasicFrame{
public:
    BasicFrame(uint32_t packetLength, uint32_t radiotapLength, u_char* data);
    ~BasicFrame();
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
    virtual void parse() = 0;
    virtual void resend() = 0;
    virtual void recombination() = 0;
protected:
    ieee80211_mgmt* mgmt;
};

class ProbeRequestFrame : public SubBasicFrame {
public:
    ProbeRequestFrame(uint32_t packetLength, uint32_t radiotapLength, u_char* data);
    ~ProbeRequestFrame();
    void parse() override;
    void resend() override;
    void recombination() override;

private:
    ieee80211_ie *ie;
};


bool SubBasicFrame::isProbeRequest(){
    return ieee80211_is_probe_req(mgmt->frame_control);
}

#endif // __BASICFRAME__
