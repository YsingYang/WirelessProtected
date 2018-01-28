#include "Data.h"

uint32_t Data::appleVendorOUI[3] =  {0x00, 0x50, 0xf2};

uint32_t* Data::getAppleVendorOUI() {
    return appleVendorOUI;
}
