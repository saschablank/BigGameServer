#pragma once
#include <mariadb/conncpp.hpp> 
#include "ISqlQueryExecutor.h"


class MariaDbSqlQueryExecutor : public ISqlQueryExecutor {
public:
    

public:
    MariaDbSqlQueryExecutor();
    ~MariaDbSqlQueryExecutor() override;
    void connect() override;
    void readTableColumns(SqlTable& table) override;
    SqlTableRecords readAllFromTable(SqlTable& table) override;

private:
    sql::Driver* driver = nullptr;
    std::unique_ptr<sql::Connection> conn = nullptr;
};