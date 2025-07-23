#pragma once

#include "../webserver/RestEndpoint.h"

class AuthRestEndpoint : public RestEndpoint {
public:
    AuthRestEndpoint() {
        endpoint_name = "AuthEndpoint";
        endpoint_path = "auth";
    }
    virtual ~AuthRestEndpoint() = default;

    std::string handleRequest(const httplib::Request& req) override;
};