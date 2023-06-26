#include "DatabaseManager.hpp"
#include <iostream>
#include "sqlite3.h"

DatabaseManager::DatabaseManager(const std::string& dbPath) {
    sqlite3_open(dbPath.c_str(), &db);
    createTable();
}

DatabaseManager::~DatabaseManager() {
    sqlite3_close(db);
}

void DatabaseManager::createTable() {
    const char* sql = "CREATE TABLE IF NOT EXISTS players("
                      "username TEXT PRIMARY KEY,"
                      "password TEXT NOT NULL,"
                      "wins INTEGER DEFAULT 0);";

    char* errorMessage = 0;
    int result = sqlite3_exec(db, sql, 0, 0, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "Error creating table: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

void DatabaseManager::addPlayer(const std::string& username, const std::string& password) {
    std::string sql = "INSERT INTO players (username, password) VALUES (?, ?);";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    int result = sqlite3_step(stmt);

    if (result != SQLITE_DONE) {
        std::cerr << "Error inserting data: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}
