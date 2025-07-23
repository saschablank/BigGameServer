#pragma once

#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <crypt.h>


class BGSCrypto {
public:
    static std::string HashValue(const std::string& value_to_hash){
        int ret;
        std::string salt = BGSCrypto::gensalt();
        char* hash = crypt(value_to_hash.c_str(), salt.c_str());
        return std::string(hash);
    }


    static std::string gensalt(size_t length=32, const std::string& salt_prefix="$6$" ) {
        std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
        if (!urandom) {
            throw std::runtime_error("Cannot open /dev/urandom");
        }
        std::ostringstream salt;
        const char charset[] = "abcdefghijklmnopqrstuvwxyz"
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "0123456789./";
        const size_t charset_size = sizeof(charset) - 1;
    
        for (size_t i = 0; i < length; ++i) {
            char byte;
            urandom.read(&byte, 1);
            salt << charset[static_cast<unsigned char>(byte) % charset_size];
        }
        return salt_prefix + salt.str() + "$";  // For SHA-512
    }

    static bool CheckValue(const std::string& value, const std::string& hash) {
        char* result_of_check = crypt(value.c_str(), hash.c_str());
        return !strcmp(value.c_str(), hash.c_str()) == 0;
    }
};