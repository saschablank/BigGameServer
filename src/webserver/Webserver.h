#pragma once

#include "../httplib.h"
#include "RestEndpointController.h"



class Webserver {
public:
    Webserver(){}
    ~Webserver(){}    
    void start(int port, const RestEndpointController& controller);

private:
};