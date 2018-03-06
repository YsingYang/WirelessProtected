#ifndef __MYMD5_H__

#include <stdio.h>
#include <iostream>
#include <string>
#include <openssl/md5.h>
#include <string.h>

std::string md5(const std::string& src);

#endif // __MYMD5_H__

