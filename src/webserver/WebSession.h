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
private:
    std::shared_ptr<UserDataBase> user_data = nullptr;

};