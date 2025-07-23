#include "Webserver.h"
#include <iostream>

using namespace httplib;

static bool IS_WEBSERVER_RUNNING = false;

void webserverThreadStart(int port, RestEndpointController* controller ){
    if( IS_WEBSERVER_RUNNING == false) {
        IS_WEBSERVER_RUNNING = true;
        httplib::Server srv;
        srv.Get(R"(^/[\w\d\/]+)", [controller](const Request& req, Response& res) {
            RestEndpoint* rest_endpoint = controller->getEndpointByPath(req.path);
            std::cout<<"Handle Request: "<< rest_endpoint->getEndpointPath()<<std::endl;
            std::string res_str = rest_endpoint->handleRequest(req);
            if (res_str.empty()) {
                res.status = 404; // Not Found
                res.set_content("Endpoint not found", "text/plain");
            }else{
                res.status = 200; // OK
                res.set_content(res_str, "application/json");
            }
        });
        srv.Post(R"(^/[\w\d\/]+)", [controller](const Request& req, Response& res) {
            RestEndpoint* rest_endpoint = controller->getEndpointByPath(req.path);
            std::cout<<"Handle Request: "<< rest_endpoint->getEndpointPath()<<std::endl;
            std::string res_str = rest_endpoint->handleRequest(req);
            if (res_str.empty()) {
                res.status = 404; // Not Found
                res.set_content("Endpoint not found", "text/plain");
            }else{
                res.status = 200; // OK
                res.set_content(res_str, "application/json");
            }
        });
        
        std::cout << "[Web] HTTP server running on http://localhost:4443\n";

        srv.listen("0.0.0.0", port);
    }
}



void Webserver::start(int port, RestEndpointController& controller)
{    
    
    std::thread webserver_thread(webserverThreadStart, port, &controller);
    webserver_thread.detach();
}