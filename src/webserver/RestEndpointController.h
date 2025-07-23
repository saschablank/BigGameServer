#pragma once
#include <string>
#include <map>
#include "RestEndpoint.h"
#include "../utils/Helper.h"

typedef std::string EndpointPath;

class RestEndpointController {
public:
    RestEndpointController() = default;
    ~RestEndpointController() = default;  

    virtual void handleRequest(const std::string& endpoint_path, const httplib::Request& req);
    virtual void register_endpoint(RestEndpoint* endpoint);

    virtual const std::map<std::string, RestEndpoint*>& getEndpoints() const;
    virtual RestEndpoint* getEndpointByPath(const std::string& path);

private:
    std::map<EndpointPath, RestEndpoint*> _endpoints;
};