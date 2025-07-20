#pragma once

#include "../webserver/RestEndpoint.h"


class AvailabilityEndpoint : public RestEndpoint {
public:
    AvailabilityEndpoint() {
        endpoint_name = "AvailabilityEndpoint";
        endpoint_path = R"(/availability)";
    }
    virtual ~AvailabilityEndpoint() = default;

    std::string handleRequest(const httplib::Request& req) override{
        if (req.method == "GET") {
            // Handle availability check logic here
            return std::string("{\"status\": \"success\"}");
        }
        return std::string("{\"status\": \"error\", \"message\": \"Method not allowed\"}");
    }
};