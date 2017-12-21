#ifndef __BASICFRAME__
#include "./ieee80211.h"

class BasicFrame{
public:
    BasicFrame();
    ~BasicFrame();
private;

};

class SubBasicFrame : public BasicFrame{
public:
    SubBasicFrame();
    ~SubBasicFrame();
private:
    ieee80211_hdr* hdr;
};

class SubBasicFrame3Addr : public BasicFrame{
public:
    SubBasicFrame3Addr();
    ~SubBasicFrame3Addr();
private:
    ieee80211_hdr_3addr* hdr;
};

class SubBasicFrameQos :public BasicFrame {
public:
    SubBasicFrameQos();
    ~SubBasicFrameQos();
private:
    ieee80211_qos_hdr* hdr;
};


#endif // __BASICFRAME__
