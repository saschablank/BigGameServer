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
            std::cout << "[Web] Registering endpoint: " << " at path: " << path << std::endl;
            svr.Get(path, [&rest_endpoint](const Request& req, Response& res) {
                std::string res_str = rest_endpoint->handleRequest(req);
                if (res_str.empty()) {
                    res.status = 404; // Not Found
                    res.set_content("Endpoint not found", "text/plain");
                }else{
                    res.status = 200; // OK
                    res.set_content(res_str, "application/json");
                }
                
            });
        }
        std::cout << "[Web] HTTP server running on http://localhost:4443\n";
        svr.listen("0.0.0.0", port);  
    }).detach();
}