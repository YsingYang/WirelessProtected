#ifndef __DATA__
#define __DATA__

#include <stdint.h>
#include <random>

//写好随机数与proberequest checkfunction
class Data {
public:
    static uint32_t* getAppleVendorOUI();
    static std::string getRandomSSID();

private:
    static int getRandomNumber();
    static std::default_random_engine _engine;
    static std::uniform_int_distribution<unsigned> _uniformIntDistribution;
    static uint32_t appleVendorOUI[3];
};



#endif // __DATA__
