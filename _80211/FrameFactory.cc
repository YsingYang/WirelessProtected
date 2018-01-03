#include "FrameFactory.h"


FrameFactory* FrameFactory::singleton = nullptr;

// 构建函数
std::shared_ptr<SubBasicFrame> createFrame(uint32_t packetLength, uint32_t radiotapLength, u_char* data) {
    if(radiotapLength > packetLength){
        printf("exceeding packet size\n");
        exit(0);
    }

    ieee80211_mgmt *mgmtData = (ieee80211_mgmt*) (data);
    int frameControl = mgmtData -> frame_control;  //不用转le16_to_cpu
    std::shared_ptr<SubBasicFrame> product = nullptr;
    if(ieee80211_is_probe_req(frameControl)) { //创建probe request

        product =   std::make_shared<ProbeRequestFrame>(packetLength, radiotapLength, data); //创建子类
    }
    return product;
}


void FrameFactory::createInstance() {
    if(singleton == nullptr) { //不保证线程安全
        singleton = new FrameFactory();
    }
}


