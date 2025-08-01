#pragma once
#include <string>
#include <regex>
#include "../httplib.h"


class RestEndpoint {
public:
    RestEndpoint() = default;
    virtual ~RestEndpoint() = default;  
    virtual std::string handleRequest(const httplib::Request& req) = 0;
    virtual std::string getEndpointName() const {
        return endpoint_name;
    }
    virtual std::string getEndpointPath() const {
        return endpoint_path;
    }
protected:
    std::string endpoint_name;
    std::string endpoint_path;

};
