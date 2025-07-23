#include "TestRSAKeyPair.h"
#include <iostream>
#include <assert.h>
#include "../../utils/RSAKeyPair.h"


int TestRSAKeyPair::setup()
{
    return 0;
}

int TestRSAKeyPair::run()
{
    RSAKeyPair pair;
    assert(RSAKeyPair::verify(pair.private_key_pem, pair.public_key_pem) == true);
    RSAKeyPair pair2;
    assert(RSAKeyPair::verify(pair2.private_key_pem, pair.public_key_pem) == false);
    std::cout <<"TestRSAKeyPair passed" << std::endl;
    return 0;
}

int TestRSAKeyPair::cleanup()
{
    return 0;
}
