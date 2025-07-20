#include "RestEndpointController.h"



void RestEndpointController::handleRequest(const std::string &endpoint_path, const httplib::Request &req, httplib::Response &res)
{
    if (endpoints.find(endpoint_path) != endpoints.end()) {
        // Call the appropriate endpoint handler
        endpoints[endpoint_path]->handleRequest(req, res);
    } else {
        // Endpoint not found, return 404
        res.status = 404;
        res.set_content("Endpoint not found", "text/plain");
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
