#include "MariaDbSqlQueryExecutor.h"
#include <iostream>


std::string ISqlQueryExecutor::DB_IP;
int ISqlQueryExecutor::DB_PORT;
std::string ISqlQueryExecutor::DB_USER;
std::string ISqlQueryExecutor::DB_PASSWORD;
std::string ISqlQueryExecutor::DB_NAME;

MariaDbSqlQueryExecutor::MariaDbSqlQueryExecutor()
{
    driver = sql::mariadb::get_driver_instance();
}

MariaDbSqlQueryExecutor::~MariaDbSqlQueryExecutor()
{
    if (conn) {
        conn->close();
    }
}


void MariaDbSqlQueryExecutor::connect()
{
    try {
        sql::SQLString url("jdbc:mariadb://172.18.0.2:3306/shipbattle");

        sql::Properties properties({
            {"user", "shipbattle_user"},
            {"password", "fu0zi2ooT6ahshei9LeoDi7puiL2ieX4"}
        });
        this->conn = std::unique_ptr<sql::Connection>(driver->connect(url, properties));
    }catch (sql::SQLException &e) {
        std::cerr << "Error reading table columns: " << e.what() << std::endl;
    }
}

void MariaDbSqlQueryExecutor::readTableColumns(SqlTable &table)
{
    if( !conn ) {
        connect();
    }
    try {
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::string query = "SHOW COLUMNS FROM " + table.table_name;
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
        
        while (res->next()) {
            std::string column_name = std::string(res->getString("Field"));
            
            std::string column_type = std::string(res->getString("Type"));
            if( column_name != table.pk_column_name) {
                table.columns[column_name] = column_type;
            }
        }
    } catch (sql::SQLException &e) {
        std::cerr << "Error reading table columns: " << e.what() << std::endl;
    }
    for( auto& it : table.columns){
        std::cout<<it.first <<" : " << it.second<<std::endl;
    }
}

SqlTableRecords MariaDbSqlQueryExecutor::readAllFromTable(SqlTable &table)
{
    SqlTableRecords records;
    if( !conn ) {
        connect();
    }
    try {
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::string query = "SELECT * FROM " + table.table_name;
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
        while (res->next()) {
            int row_pk_value = res->getInt(table.pk_column_name);
            records[row_pk_value] = std::map<std::string, SqlFieldValue>();
            for( const auto& it : table.columns)
            {
                if(it.second.find("varchar") != std::string::npos || it.second.find("timestamp") != std::string::npos) //field is a string
                {
                    SqlFieldValue value = std::string(res->getString(it.first));
                    records[row_pk_value][it.first] = value;
                }
                else if(it.second.find("int") != std::string::npos) // field is a int
                {
                    SqlFieldValue value = res->getInt(it.first);
                    records[row_pk_value][it.first] = value;
                }
            }
        }
    } catch (sql::SQLException &e) {
        std::cerr << "Error reading table : " << e.what() << std::endl;
        return SqlTableRecords();
    }
    return records;
}

bool MariaDbSqlQueryExecutor::insert_into(SqlTable &table, const SqlRecord &record_to_insert)
{
    if( !conn ) {
        connect();
    }
    std::string field_names_to_insert;
    std::string place_holder_pice;
    for(const auto& it : record_to_insert) {
        field_names_to_insert += it.first + ",";
        place_holder_pice += "?,";
    }
    if (field_names_to_insert.empty() == false && place_holder_pice.empty() == false) {
        field_names_to_insert.pop_back();
        place_holder_pice.pop_back();
    }
    try {
        std::unique_ptr<sql::PreparedStatement> stmt
        (
            conn->prepareStatement("INSERT INTO " + table.table_name + "(" + field_names_to_insert + ") VALUES (" + place_holder_pice + ")")
        );
        int counter = 1;
        for(const auto& it : record_to_insert) {
            std::string field_name = it.first;
            if(table.columns.find(it.first) != table.columns.end()) {

                std::string datatype = table.columns[field_name];
                if(datatype.find("varchar") != std::string::npos) {
                    stmt->setString(counter,std::get<std::string>(it.second));     
                }
                else if( datatype == "timestamp"){
                    stmt->setDateTime(counter, std::get<std::string>(it.second));
                }
                else if(datatype.find("int") != std::string::npos) {
                    stmt->setInt(counter, std::get<int>(it.second));
                }

            }
            ++counter;
        }
        stmt->executeUpdate();
    } catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
    return true;
}
