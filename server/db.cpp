#include "db.hpp"
#include <iostream>

std::vector<std::string> GetUsers() {
    sqlite3* DB; 
    sqlite3_stmt* stmt;
    std::vector<std::string> users;

    int exit = sqlite3_open("example.db", &DB);
    if (exit != SQLITE_OK) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return users;
    }

    std::string query = "SELECT username FROM users";
    
    exit = sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, NULL);

    if (exit != SQLITE_OK) {
        std::cerr << "Error prepare " << sqlite3_errmsg(DB) << std::endl;
        return users;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        users.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);

    return users;
}
