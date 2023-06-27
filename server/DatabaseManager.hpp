#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <sqlite3.h>
#include <string>
#include <mutex>

class DatabaseManager {
public:
    DatabaseManager(const std::string& dbPath);
    ~DatabaseManager();
    void createTable();
    void addPlayer(const std::string& username, const std::string& password);
    bool registerPlayer(const std::string& username, const std::string& password);
    bool authenticatePlayer(const std::string& username, const std::string& password);
    
private:
    sqlite3* db;
    std::mutex dbMutex;
    
};

#endif // DATABASEMANAGER_H
