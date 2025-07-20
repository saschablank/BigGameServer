#pragma once
#include <string>
#include <map>
#include "RestEndpoint.h"


class RestEndpointController {
public:
    RestEndpointController() = default;
    ~RestEndpointController() = default;  
    virtual void handleRequest(const std::string& endpoint_path, const httplib::Request& req, httplib::Response& res);
    virtual void register_endpoint(RestEndpoint* endpoint);
    virtual const std::map<std::string, RestEndpoint*>& geEtndpoints() const {
        return endpoints;
    }

private:
    std::map<std::string, RestEndpoint*> endpoints; // Maps endpoint names to their handlers
    

};