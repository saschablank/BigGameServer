#pragma once

#include "ITestExecutor.h"



class BGSTestExecutor : public ITestExecutor{
public:
    BGSTestExecutor() {}
    ~BGSTestExecutor();
    void instantiateTests() override;
    int runTests() override;
};