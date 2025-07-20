#pragma once

#include "../webserver/RestEndpoint.h"

class AuthRestEndpoint : public RestEndpoint {
public:
    AuthRestEndpoint() {
        endpoint_name = "AuthEndpoint";
        endpoint_path = R"(/auth)";
    }
    virtual ~AuthRestEndpoint() = default;

    void handleRequest(const httplib::Request& req, httplib::Response& res) override;
};