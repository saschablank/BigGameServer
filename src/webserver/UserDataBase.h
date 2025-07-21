#pragma once
#include <string>
#include <variant>
#include <map>

typedef std::variant<int, double, std::string> UserDataValue;

class UserDataBase{
    
public:
    UserDataBase() = default;
    virtual ~UserDataBase() = default;
    virtual void set_data(const std::string key, const UserDataValue value);
    virtual const UserDataValue* get_data(const std::string key);
    virtual void remove_data(const std::string key);
    virtual bool has_data(const std::string key) const;

protected:
    std::map<std::string, UserDataValue> data_store{}; // Store user data as key-value pairs
};