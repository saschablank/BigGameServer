#pragma once
#include <variant>
#include <string>
#include <map>
#include <memory>
#include <mariadb/conncpp.hpp> 


class SqlTable{
public:
    SqlTable(const std::string& table_name) { this->table_name = table_name; };
    ~SqlTable() = default;
    SqlTable(const SqlTable&) = delete;
    SqlTable& operator=(const SqlTable&) = delete;

    
    std::string table_name;
    std::map<std::string, std::string> columns;
    
};