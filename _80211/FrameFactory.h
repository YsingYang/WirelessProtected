#ifndef __FRAMEFACTORY_H__
#include "BasicFrame.h"

class FrameFactory {
public:
    static void  createInstance();

    SubBasicFrame* produced();
private:
    SubBasicFrame() {}

    static FrameFactory* singleton = nullptr;
};



#endif // __FRAMEFACTORY_H__
