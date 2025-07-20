#include "UserDataBase.h"

void UserDataBase::set_data(const std::string key, const UserDataValue value)
{
    data_store[key] = value;   
}

const UserDataValue* UserDataBase::get_data(const std::string key)
{
    auto it = data_store.find(key);
    if (it != data_store.end()) {
        return &it->second;
    }
    return nullptr;
}

void UserDataBase::remove_data(const std::string key)
{    
    auto it = data_store.find(key);
    if (it != data_store.end()) {
        data_store.erase(it);
    }
}

bool UserDataBase::has_data(const std::string key) const
{   
    return data_store.find(key) != data_store.end();
}
