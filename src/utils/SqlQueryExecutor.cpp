#include "SqlQueryExecutor.h"
#include <iostream>

std::string SqlQueryExecutor::DB_IP;
int SqlQueryExecutor::DB_PORT;
std::string SqlQueryExecutor::DB_USER;
std::string SqlQueryExecutor::DB_PASSWORD;
std::string SqlQueryExecutor::DB_NAME;

SqlQueryExecutor::SqlQueryExecutor()
{
    driver = sql::mariadb::get_driver_instance();
}

SqlQueryExecutor::~SqlQueryExecutor()
{
    if (conn) {
        conn->close();
        delete driver;
    }
}



void SqlQueryExecutor::executeQuery(const std::string &query)
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

void SqlQueryExecutor::connect()
{
    std::string url_str = "jdbc:mariadb://" + DB_IP +":" + std::to_string(DB_PORT) + "/" + DB_NAME;
    sql::Properties properties({{"user", DB_USER}, {"password", DB_PASSWORD}});
    this->conn = std::unique_ptr<sql::Connection>(driver->connect(url_str, properties));
    if (!conn) {
        throw std::runtime_error("Failed to connect to the database");
    }
}
