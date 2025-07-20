#pragma once
#include <string>
#include "SqlTable.h"



class ISqlQueryExecutor {
public:
    static std::string DB_IP;
    static int DB_PORT;
    static std::string DB_USER;
    static std::string DB_PASSWORD;
    static std::string DB_NAME;
    
    static void set_connection_details(const std::string p_db_ip, int p_db_port, const std::string p_db_user, const std::string p_db_password, const std::string p_db_name){
        ISqlQueryExecutor::DB_IP       = p_db_ip;
        ISqlQueryExecutor::DB_PORT     = p_db_port;
        ISqlQueryExecutor::DB_USER     = p_db_user;
        ISqlQueryExecutor::DB_PASSWORD = p_db_password;
        ISqlQueryExecutor::DB_NAME     = p_db_name;
    }


    virtual ~ISqlQueryExecutor() = default;

    virtual void readTableColumns(SqlTable& table) = 0;

protected:
    virtual void connect() = 0;
};