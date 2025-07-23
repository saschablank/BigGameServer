#include "BGSTestExecutor.h"
#include "BGStests/TestRSAKeyPair.h"
#include "BGStests/TestBGSCrypto.h"

BGSTestExecutor::~BGSTestExecutor()
{
    for( IUnitTest* test : _tests) {
        delete test;
    }
    _tests.clear();
}


void BGSTestExecutor::instantiateTests()
{
    IUnitTest* key_pair_test = new TestRSAKeyPair();
    _tests.push_back(key_pair_test);
    IUnitTest* bg_crypto_test = new TestBGSCrypto();
    _tests.push_back(bg_crypto_test);
}


int BGSTestExecutor::runTests()
{
    int test_result = 0;
    for( IUnitTest* test : _tests) {
        test_result = test->setup();
        test_result = test->run();
        test_result = test->cleanup();
    }
    return test_result;
}