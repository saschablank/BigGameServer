#pragma once

#include "../webserver/RestEndpoint.h"


class GetKeyEndpoint : public RestEndpoint {
public:
GetKeyEndpoint() {
        endpoint_name = "GetKeyEndpoint";
        endpoint_path = R"(/getkey/)";
    }
    virtual ~GetKeyEndpoint() = default;

    std::string handleRequest(const httplib::Request &req) override;
};