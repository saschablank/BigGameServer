#pragma once
#include "../IUnitTest.h"

class TestBGSCrypto: public IUnitTest
{
public:
    TestBGSCrypto() = default;
    ~TestBGSCrypto() = default;

    int setup() override;
    int run() override;
    int cleanup() override;
};