#include "Webserver.h"
#include <iostream>


using namespace httplib;
void Webserver::start(int port, const RestEndpointController& controller)
{
    std::thread([port, controller]() {
        httplib::Server svr;
        RestEndpointController local_controller = controller;
        for (const auto& endpoint : local_controller.geEtndpoints()) {
            const std::string& path = endpoint.first;
            RestEndpoint* rest_endpoint = endpoint.second;
            std::cout << "[Web] Registering endpoint: " << rest_endpoint->getEndpointName() << " at path: " << path << std::endl;
            svr.Get(path, [rest_endpoint](const Request& req, Response& res) {
                rest_endpoint->handleRequest(req, res);
            });
        }
        //svr.Get("(\\/*\\w*\\d*)", [&](const Request& req, Response& res) {
        //    for(auto& endpoint : local_controller.geEtndpoints()) {
        //        const std::string& path = endpoint.first;
        //        RestEndpoint* rest_endpoint = endpoint.second;
        //        if (req.path == path) {
        //            rest_endpoint->handleRequest(req, res);
        //            break;
        //        }
        //    }
        //  });
        
        std::cout << "[Web] HTTP server running on http://localhost:4443\n";
        svr.listen("0.0.0.0", port);  // Use 80 if you run as root
    }).detach();
}