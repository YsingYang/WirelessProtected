#ifndef __DATA__
#define __DATA__

#include <stdint.h>

class Data {
public:
    static char* getAppleVendorOUI();

private:
    static uint32_t appleVendorOUI[3];
};



#endif // __DATA__
