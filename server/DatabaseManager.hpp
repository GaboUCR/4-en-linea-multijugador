#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <sqlite3.h>
#include <string>

class DatabaseManager {
public:
    DatabaseManager(const std::string& dbPath);
    ~DatabaseManager();

    void addPlayer(const std::string& username, const std::string& password);

private:
    sqlite3* db;

    void createTable();
};

#endif // DATABASEMANAGER_H
