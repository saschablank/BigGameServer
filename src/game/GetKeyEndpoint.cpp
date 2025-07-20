#include "GetKeyEndpoint.h"
#include <iostream>



std::string GetKeyEndpoint::handleRequest(const httplib::Request &req)
{
    return std::string("{\"status\": \"success\", \"message\": \"Key retrieved successfully\"}");
}