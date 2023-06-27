#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <sqlite3.h>
#include <string>

class DatabaseManager {
public:
    DatabaseManager(const std::string& dbPath);
    ~DatabaseManager();
    void createTable();
    void addPlayer(const std::string& username, const std::string& password);
    bool registerPlayer(const std::string& username, const std::string& password);
    bool authenticatePlayer(const std::string& username, const std::string& password);
    std::tuple<int, int> getPlayerWinLossRecord(const std::string& username);
private:
    sqlite3* db;
    
};

#endif // DATABASEMANAGER_H
