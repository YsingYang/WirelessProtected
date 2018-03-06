#ifndef __DATA__
#define __DATA__

#include <stdint.h>
#include <random>

//写好随机数与proberequest checkfunction

class Data {
public:
    static uint32_t* getAppleVendorOUI();
    static std::string getRandomSSID();
    static std::string getSSID(int index); //数据默认存在程序中

private:
    static int getRandomNumber();
    static std::default_random_engine _engine;
    static std::uniform_int_distribution<unsigned> _uniformIntDistribution;
    static uint32_t appleVendorOUI[3];
    static std::vector<std::string> SSID_SET;
};



#endif // __DATA__
