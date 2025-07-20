#pragma once
#include <string>
#include <mariadb/conncpp.hpp>



class SqlQueryExecutor {
public:
    static std::string DB_IP;
    static int DB_PORT;
    static std::string DB_USER;
    static std::string DB_PASSWORD;
    static std::string DB_NAME;
    
    SqlQueryExecutor();
    ~SqlQueryExecutor();
    static void set_connection(const std::string p_db_ip, int p_db_port, const std::string p_db_user, const std::string p_db_password, const std::string p_db_name){
        SqlQueryExecutor::DB_IP       = p_db_ip;
        SqlQueryExecutor::DB_PORT     = p_db_port;
        SqlQueryExecutor::DB_USER     = p_db_user;
        SqlQueryExecutor::DB_PASSWORD = p_db_password;
        SqlQueryExecutor::DB_NAME     = p_db_name;
    }
    void executeQuery(const std::string& query);


private:
    
    sql::Driver* driver = nullptr;
    std::unique_ptr<sql::Connection> conn = nullptr;

    void connect();
};