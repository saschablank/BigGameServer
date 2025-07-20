#include "GetKeyEndpoint.h"
#include <iostream>



void GetKeyEndpoint::handleRequest(const httplib::Request &req, httplib::Response &res)
{   auto subpath = req.matches[1];
    std::cout << subpath << std::endl;
    if (req.method == "GET") {
        // Handle availability check logic here
        res.status = 200; // OK
        res.set_content("{\"status\": \"success\"}", "application/json");
    } else {
        res.status = 405; // Method Not Allowed
        res.set_content("Method not allowed", "text/plain");
    }
}