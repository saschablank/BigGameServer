#include "RestEndpointController.h"



void RestEndpointController::handleRequest(const std::string &endpoint_path, const httplib::Request &req)
{
    if (_endpoints.find(endpoint_path) != _endpoints.end()) {
        // Call the appropriate endpoint handler
        _endpoints[endpoint_path]->handleRequest(req);
    } else {
        // Endpoint not found, return 404
        
        std::cerr << "Endpoint not found: " << endpoint_path << std::endl;
    }
}

void RestEndpointController::register_endpoint(RestEndpoint *endpoint)
{
    if (endpoint) {
        _endpoints[endpoint->getEndpointPath()] = endpoint;
    } else {
        std::cerr << "Attempted to register a null endpoint." << std::endl;
    }
}

const std::map<std::string, RestEndpoint *> &RestEndpointController::getEndpoints() const
{
    return _endpoints;
}

RestEndpoint *RestEndpointController::getEndpointByPath(const std::string &path)
{
    if(_endpoints.find(path) != _endpoints.end()){
        return _endpoints[path];
    }
    std::vector<std::string_view>path_split = Helper::split(path, '/'); 
    if(path_split.size() > 1) {
        std::string base_path(path_split[1]);
        if(_endpoints.find(base_path) != _endpoints.end()){
            return _endpoints[base_path];
        }
    }
    return nullptr;
}
