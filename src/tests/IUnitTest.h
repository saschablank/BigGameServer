#pragma once


class IUnitTest {
public:
    IUnitTest() = default;
    virtual ~IUnitTest() = default;

    virtual int setup() = 0;
    virtual int run() = 0;
    virtual int cleanup() = 0;

};