#pragma once

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <random>
#include <sstream>
#include <iomanip>
#include "WebSession.h"


class SessionManager {
    public:
        static SessionManager& getInstance() {
            static SessionManager instance; // Thread-safe in C++11 and above
            return instance;
        }
    
        // Delete copy and move semantics
        SessionManager(const SessionManager&) = delete;
        SessionManager& operator=(const SessionManager&) = delete;
        SessionManager(SessionManager&&) = delete;
        SessionManager& operator=(SessionManager&&) = delete;

        bool hasSession(const std::string& session_id) const {
            return _sessions.find(session_id) != _sessions.end();
        }

        const std::string& createNewSession() {
            std::string new_session_id = _generate_session_id();
            _sessions[new_session_id] = std::make_shared<WebSession>();
            return _sessions.find(new_session_id)->first;
        }

        std::shared_ptr<WebSession> getSession(const std::string& session_id) {
            auto it = _sessions.find(session_id);
            if (it != _sessions.end()) {
                return it->second;
            }
            return nullptr; // Session not found
        }

    
    private:
    SessionManager() {
            // Constructor logic
        }

        ~SessionManager() {
            // Destructor logic
        }

    
    std::string _generate_session_id(size_t length = 64) {
        std::random_device rd;
        std::mt19937_64 eng(rd()); // 64-bit Mersenne Twister
        std::uniform_int_distribution<uint64_t> dist;

        std::ostringstream ss;
        size_t chunks = length / 16 + 1; // 16 hex chars = 64 bits

        for (size_t i = 0; i < chunks; ++i) {
            uint64_t random_value = dist(eng);
            ss << std::hex << std::setw(16) << std::setfill('0') << random_value;
        }
        std::cout<< "Generated session ID: " << ss.str() << std::endl;
        return ss.str().substr(0, length);
    }
    
    std::map<std::string, std::shared_ptr<WebSession>> _sessions;
};
