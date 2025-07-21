#pragma once

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <random>
#include <sstream>
#include <iomanip>
#include "WebSession.h"
#include "../utils/SqlTable.h"
#include "../utils/MariaDbSqlQueryExecutor.h"

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
            MariaDbSqlQueryExecutor query;
            query.readTableColumns(_table);
            SqlTableRecords db_sessions = query.readAllFromTable(_table);
            for (const auto& row : db_sessions) {
                std::shared_ptr<WebSession> new_session = std::make_shared<WebSession>(WebSession());
                std::map<std::string, SqlFieldValue> field_values = row.second;
                const std::string* user_id = std::get_if<std::string>(&field_values["user_id"]);
                new_session->user_id = *user_id;
                const int* logged_in = std::get_if<int>(&field_values["is_logged_in"]);
                new_session->is_logged_in = *logged_in;
                const std::string* session_expire = std::get_if<std::string>(&field_values["session_expired_at"]);
                new_session->session_expire_at = *session_expire;

                const std::string* session_id = std::get_if<std::string>(&field_values["session_id"]);
                this->_sessions[*session_id] = new_session;
                
            }

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
    SqlTable _table = SqlTable("user_sessions", "id");
    
    
};
