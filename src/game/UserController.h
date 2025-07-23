#pragma once

#include <map>
#include <string>
#include <memory>
#include "../webserver/UserDataBase.h"
#include "../utils/MariaDbSqlQueryExecutor.h"
#include "../utils/SqlTable.h"


class UserController{
public:
    UserController();
    virtual ~UserController(){};

    std::shared_ptr<UserDataBase> getUserById(const int id);
    const int createNewUser(const std::string& player_name);
    bool deleteUser(const int id);
    bool updateUserData(std::shared_ptr<UserDataBase> user_data);



private:
    std::map<int, std::shared_ptr<UserDataBase>> _users;
    SqlTable _table = SqlTable("users", "id");
    MariaDbSqlQueryExecutor _query;
};