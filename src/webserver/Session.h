#pragma once
#include <string>
#include <memory>
#include "IUserData.h"

class Session {
public:
    Session() = default;
    Session(const Session&) = delete; // Disable copy constructor
    Session& operator=(const Session&) = delete; // Disable copy assignment
private:
    std::string session_id;
    std::shared_ptr<IUserData> user_data;

};