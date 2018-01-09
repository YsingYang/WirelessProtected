#ifndef __FRAMEFACTORY_H__
#define __FRAMEFACTORY_H__
#include <memory>

#include "BasicFrame.h"
#include "ieee80211.h"

std::shared_ptr<SubBasicFrame> createFrame(uint32_t packetLength, uint32_t radiotapLength, u_char* data);

class FrameFactory {
public:
    static void  createInstance();

    SubBasicFrame* produced(uint32_t packetLength, uint32_t radiotapLength, u_char* data);
private:
    FrameFactory() {}

    static FrameFactory* singleton;
};



#endif // __FRAMEFACTORY_H__
