#include "AuthRestEndpoint.h"
#include "../webserver/SessionManager.h"
#include "../utils/Helper.h"
#include "../utils/RSAKeyPair.h"


std::string AuthRestEndpoint::handleRequest(const httplib::Request &req)
{
    std::cout<<"endpoint called :" + req.path << std::endl;
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
    else if( req.method == "POST"){
        if(req.path == "/auth/newkey"){
            std::map<std::string, std::string>req_params = Helper::ReadReqBodyParameters(req.body);
            SessionManager& sessionManager = SessionManager::getInstance();
            if( req_params.find("session_id") != req_params.end())
            {
                std::shared_ptr<WebSession> session = sessionManager.getSession(req_params["session_id"]);
                if( session == nullptr)
                {
                    std::map<std::string, std::string> response_data{
                        {"status", "error"},
                        {"msg", "seession_id not valid"}
                    };
                    return Helper::string_map_to_json_str(response_data);
                }
                RSAKeyPair pair;
               
                std::map<std::string, std::string> response_data{
                    {"status", "success"},
                    {"key", pair.private_key_pem}
                };
                return Helper::string_map_to_json_str(response_data);
            }

        }
    }
    return std::string();
}