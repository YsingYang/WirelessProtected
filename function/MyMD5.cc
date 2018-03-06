#include "./MyMD5.h"

std::string md5(const std::string& src){
    MD5_CTX ctx;
    std::string md5_result;
    u_char md[16] = {0};

    char tmp[33] = {0};

    MD5_Init(&ctx);
    MD5_Update(&ctx, src.c_str(), src.size());
    MD5_Final(md, &ctx);

    for(int i = 0; i < 16; ++i) {
        memset(tmp, 0x00, sizeof(tmp));
        sprintf(tmp, "%02X", md[i]); //md[i]字符， 实际是将其ascii码转化成二进制的形式给tmp
        md5_result += tmp;
    }
    return md5_result;
}
