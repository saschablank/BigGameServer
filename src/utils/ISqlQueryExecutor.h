#pragma once
#include <iostream>
#include <unistd.h> // für crypt()
#include <cstring>  // für strcmp()
#include <assert.h>


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


    static bool CheckHash(const std::string& value_to_ceck, const std::string& hash_to_check_agains){
        char* check_result_hash = crypt(value_to_ceck.c_str(), hash_to_check_agains.c_str());
        return strcmp(check_result_hash, hash_to_check_agains.c_str()) == 0;
    }


    virtual ~ISqlQueryExecutor() = default;

    virtual void readTableColumns(SqlTable& table) = 0;
    virtual SqlTableRecords readAllFromTable(SqlTable& table) = 0;
    virtual bool insert_into(SqlTable& table, const SqlRecord& record_to_insert) = 0;
    

protected:
    virtual void connect() = 0;
};