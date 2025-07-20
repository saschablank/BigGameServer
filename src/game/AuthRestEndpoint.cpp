#include "AuthRestEndpoint.h"
#include "../webserver/SessionManager.h"
#include "../utils/Helper.h"

std::string AuthRestEndpoint::handleRequest(const httplib::Request &req)
{
    if (req.method == "GET") {
     
        if( req.path == "/auth/newsession" )
        {
            SessionManager& sessionManager = SessionManager::getInstance();
            std::string session_id = sessionManager.createNewSession();
            std::map<std::string, std::string> response_data{
                {"status", "success"},
                {"session_id", session_id}
            };
            return Helper::string_map_to_json_str(response_data);
     
        }
        
    }
    return std::string("Method not allowed", "text/plain");
}