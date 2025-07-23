#include "TestBGSCrypto.h"
#include <string>
#include "../../utils/BGSCrypto.h"


int TestBGSCrypto::setup()
{
    return 0;
}

int TestBGSCrypto::run()
{
    std::string password = "hjasdf123455lkhaslkjdfhalksjhfbqwernbwebr";
    std::string wrong_password = "hasdfjashljkwnernwernwenrnn";
    std::string hash = BGSCrypto::HashValue(password);
    assert(hash.empty() == false);
    bool is_valid = BGSCrypto::CheckValue(password, hash);
    assert(is_valid == true);
    is_valid = BGSCrypto::CheckValue(wrong_password, hash);
    std::cout << "TestBGSCrypt passed" << std::endl;
    return 0;
}

int TestBGSCrypto::cleanup()
{
    return 0;
}
