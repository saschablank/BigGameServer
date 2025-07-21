#pragma once
#include <string>
#include <memory>
#include "UserDataBase.h"

class WebSession {
public:
    WebSession() = default;
    WebSession(const WebSession&) = delete; // Disable copy constructor
    WebSession& operator=(const WebSession&) = delete; // Disable copy assignment
    WebSession(WebSession&&) = default; // Enable move constructor
    std::shared_ptr<UserDataBase> getUserData();

    bool is_logged_in = false;
    std::string user_id = "-1";
    std::string session_expire_at = "";
private:
    std::shared_ptr<UserDataBase> user_data = nullptr;


};