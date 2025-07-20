#include "AuthRestEndpoint.h"

void AuthRestEndpoint::handleRequest(const httplib::Request &req, httplib::Response &res)
{
    if (req.method == "POST") {
     
        res.status = 200;
        res.set_content("Authentication successful", "text/plain");
    } else {
        res.status = 405; // Method Not Allowed
        res.set_content("Method not allowed", "text/plain");
    }
}