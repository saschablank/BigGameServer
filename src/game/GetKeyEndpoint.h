#pragma once

#include "../webserver/RestEndpoint.h"


class GetKeyEndpoint : public RestEndpoint {
public:
GetKeyEndpoint() {
        endpoint_name = "GetKeyEndpoint";
        endpoint_path = R"(/getkey/\w+)";
    }
    virtual ~GetKeyEndpoint() = default;

    void handleRequest(const httplib::Request& req, httplib::Response& res) override;
};