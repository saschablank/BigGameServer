#pragma once

#include "../webserver/RestEndpoint.h"


class AvailabilityEndpoint : public RestEndpoint {
public:
    AvailabilityEndpoint() {
        endpoint_name = "AvailabilityEndpoint";
        endpoint_path = R"(/availability)";
    }
    virtual ~AvailabilityEndpoint() = default;

    void handleRequest(const httplib::Request& req, httplib::Response& res) override{
        if (req.method == "GET") {
            // Handle availability check logic here
            res.status = 200; // OK
            res.set_content("{\"status\": \"success\"}", "application/json");
        } else {
            res.status = 405; // Method Not Allowed
            res.set_content("Method not allowed", "text/plain");
        }
    }
};