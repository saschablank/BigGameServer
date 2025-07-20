#include "HttpClient.h"
#include <iostream>


#include "httplib.h"
#include "utils/StringHelper.h"

HttpClient::HttpClient(){

}

HttpClient::~HttpClient(){

}



bool HttpClient::sendRegisterRequest(const std::string& auth_token) {
    // Implementation of sending a register request using the provided auth_token
    // For now, we will just print the auth_token to simulate the request
    std::cout << "Sending register request with auth token: " << auth_token << std::endl;
    httplib::Client cli = httplib::Client(this->server_url);
    std::string body = "{\"game_server_token\": \"aeDaiziesohooch2CahTh1eed5Oof6bi\"}";
    const char * c_str_body =  body.c_str();
    size_t body_lenght = body.size();
    httplib::UploadProgress progress = httplib::UploadProgress();
    std::string content_type = "application/json";
    auto result = cli.Post(this->register_endpoint, c_str_body , body_lenght ,content_type , progress);
    
    if(result->status != 200) {
        std::cerr << "Failed to register server: " << result.error() << std::endl;
        return false;
    }
    std::cout << result->body << std::endl;
    std::vector<std::string_view>results = StringHelper::split(result->body, ';');
    bool success = false;
    std::map<std::string, std::string> data_fields = this->process_result(results, &success);
    if(!success) {
        std::cerr << "Failed to process registration response." << std::endl;
        return false;
    }
    if(data_fields.find("session_id") != data_fields.end()) {
        this->session_id = data_fields["session_id"];
        std::cout << "Session ID: " << this->session_id << std::endl;
    } else {
        std::cerr << "Session ID not found in response." << std::endl;
        return false;
    }
    return true;
}

bool HttpClient::sendGetLevelsRequest(const std::string& auth_token)
{
    std::cout << "Sending get level request with auth token: " << auth_token << std::endl;
    httplib::Client cli = httplib::Client(this->server_url);
    std::string body = "{\"game_server_token\": \"aeDaiziesohooch2CahTh1eed5Oof6bi\"}";
    const char * c_str_body =  body.c_str();
    size_t body_lenght = body.size();
    httplib::UploadProgress progress = httplib::UploadProgress();
    std::string content_type = "application/json";
    auto result = cli.Post(this->get_levels_endpoint, c_str_body , body_lenght ,content_type , progress);
    if(result->status != 200) {
        std::cerr << "Failed to get levels: " << result.error() << std::endl;
        return false;
    }
    std::vector<std::string_view>results = StringHelper::split(result->body, '@');
    for (const auto& res : results) {
        std::cout << res << std::endl;
    }
    return true;
}

std::map<std::string, std::string> HttpClient::process_result(const std::vector<std::string_view>& data, bool* success) 
{
    std::map<std::string, std::string> data_fields = {};
    for( auto it : data) {
        std::cout<< it <<std::endl;
        auto parts = StringHelper::split(it, '=');
        if(parts.size() == 2) {
            data_fields[std::string(parts[0])] = std::string(parts[1]);
        } else {
            std::cerr << "Invalid data format: " << it << std::endl;
            if(success) *success = false;
            return {};
        }
    }
    if( data_fields.find("status") != data_fields.end() && data_fields["status"] == "success") {
        if(success) *success = true;
    } else {
        if(success) *success = false;
    }

    return data_fields;
}


