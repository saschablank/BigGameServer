#pragma once

#include "../webserver/RestEndpoint.h"

class AuthRestEndpoint : public RestEndpoint {
public:
    AuthRestEndpoint() {
        endpoint_name = "AuthEndpoint";
        endpoint_path = R"(/auth/(\w+))";
    }
    virtual ~AuthRestEndpoint() = default;

    std::string handleRequest(const httplib::Request& req) override;
};