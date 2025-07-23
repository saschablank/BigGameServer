#pragma once
#include <variant>
#include <string>
#include <map>
#include <memory>
#include <mariadb/conncpp.hpp> 


typedef std::variant<int,std::string, double>SqlFieldValue;
typedef std::map<std::string, SqlFieldValue>SqlRecord;
typedef std::map<int, SqlRecord> SqlTableRecords;


class SqlTable{
public:
    SqlTable(const std::string& table_name, const std::string pk_name) { this->table_name = table_name; this->pk_column_name = pk_name; }
    ~SqlTable() = default;
    SqlTable(const SqlTable&) = delete;
    SqlTable& operator=(const SqlTable&) = delete;

    
    std::string table_name;
    std::map<std::string, std::string> columns;
    std::string pk_column_name;

    
};