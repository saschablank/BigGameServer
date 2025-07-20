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


/*
void MariaDbSqlQueryExecutor::executeQuery(const std::string &query)
{
    try {
        if (!conn) {
            connect();
        }
        // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // Execute query
        sql::ResultSet *res = stmnt->executeQuery("select * from users");
        // Loop through and print results
        while (res->next()) {
            std::cout << "id = " << res->getInt(1);
            std::cout << ", google_user_id = " << res->getString(2);
            std::cout << ", playername = " << res->getString(3) << "\n";
        }
    }
    catch(sql::SQLException& e){
      std::cerr << "Error selecting users: " << e.what() << std::endl;
   }
   conn->close();

}
   */

void MariaDbSqlQueryExecutor::connect()
{
    std::string url_str = "jdbc:mariadb://" + DB_IP +":" + std::to_string(DB_PORT) + "/" + DB_NAME;
    sql::Properties properties({{"user", DB_USER}, {"password", DB_PASSWORD}});
    this->conn = std::unique_ptr<sql::Connection>(driver->connect(url_str, properties));
    if (!conn) {
        throw std::runtime_error("Failed to connect to the database");
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
            table.columns[column_name] = column_type;
        }
    } catch (sql::SQLException &e) {
        std::cerr << "Error reading table columns: " << e.what() << std::endl;
    }
    for( auto& it : table.columns){
        std::cout<<it.first <<" : " << it.second<<std::endl;
    }
    conn->close();
}
