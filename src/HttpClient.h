#pragma once

#include <string>
#include <map>
#include <vector>
#include <string_view>

class HttpClient{

public:
    HttpClient();
    ~HttpClient();

    bool sendRegisterRequest(const std::string& auth_token);
    bool sendGetLevelsRequest(const std::string& auth_token);

private:
    std::map<std::string, std::string> process_result(const std::vector<std::string_view>& data, bool* success);

    std::string session_id = "none";
    const std::string server_url = "http://192.168.1.245:4443";
    const std::string register_endpoint = "/registerserver";
    const std::string get_levels_endpoint = "/getlevels";
    const std::string rm_server_endpoint = "/rmserver";
    
};