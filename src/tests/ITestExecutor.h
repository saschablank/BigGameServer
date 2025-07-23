#pragma once
#include <vector>
#include <memory>
#include "IUnitTest.h"


class ITestExecutor{
public:
    ITestExecutor() = default;
    virtual ~ITestExecutor() = default;

    virtual void instantiateTests() = 0;
    virtual int runTests() = 0;
protected:
    std::vector<IUnitTest*>_tests;

};