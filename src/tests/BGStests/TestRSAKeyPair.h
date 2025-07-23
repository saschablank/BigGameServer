#pragma once

#include "../IUnitTest.h"



class TestRSAKeyPair : public IUnitTest{

public:
    TestRSAKeyPair() = default;
    ~TestRSAKeyPair() = default;

    int setup() override;
    int run() override;
    int cleanup() override;

};

