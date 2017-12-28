#include "FrameFactory.h"


void FrameFactory::createInstance() {
    if(singleton == nullptr) { //不保证线程安全
        singleton = new FrameFactory();
    }
    return singleton;
}


SubBasicFrame* FrameFactory::createInstance() {

}
