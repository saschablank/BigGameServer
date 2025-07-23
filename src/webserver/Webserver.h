#pragma once

#include "../httplib.h"
#include "RestEndpointController.h"



class Webserver {
public:
    Webserver() = default;
    // Disable copy constructor
    Webserver(const Webserver&) = delete;

    // Disable copy assignment operator
    Webserver& operator=(const Webserver&) = delete;
    ~Webserver() = default;
    void start(int port,  RestEndpointController& controller);

protected:
    httplib::Server _svr;
};