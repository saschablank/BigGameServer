#include "RestEndpointController.h"



void RestEndpointController::handleRequest(const std::string &endpoint_path, const httplib::Request &req)
{
    if (endpoints.find(endpoint_path) != endpoints.end()) {
        // Call the appropriate endpoint handler
        endpoints[endpoint_path]->handleRequest(req);
    } else {
        // Endpoint not found, return 404
        
        std::cerr << "Endpoint not found: " << endpoint_path << std::endl;
    }
}

void RestEndpointController::register_endpoint(RestEndpoint *endpoint)
{
    if (endpoint) {
        endpoints[endpoint->getEndpointPath()] = endpoint;
    } else {
        std::cerr << "Attempted to register a null endpoint." << std::endl;
    }
}
