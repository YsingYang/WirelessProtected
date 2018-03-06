#include "Data.h"

uint32_t Data::appleVendorOUI[3] =  {0x00, 0x50, 0xf2};

uint32_t* Data::getAppleVendorOUI() {
    return appleVendorOUI;
}

std::vector<std::string> Data::SSID_SET = {"abc", "edf", "gsda", "dqwe", "asdwe"};
