#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <sqlite3.h>
#include <string>
#include <vector>
class DatabaseManager {
public:
    DatabaseManager(const std::string& dbPath);
    ~DatabaseManager();
    void createTable();
    void addPlayer(const std::string& username, const std::string& password);
    bool registerPlayer(const std::string& username, const std::string& password);
    bool authenticatePlayer(const std::string& username, const std::string& password);
    std::tuple<int, int> getPlayerWinLossRecord(const std::string& username);
    void incrementPlayerLosses(const std::string& username);
    void incrementPlayerWins(const std::string& username);
    std::vector<std::tuple<std::string, int, int>> getAllPlayersWinLossRecord(); 
private:
    sqlite3* db;
    
};

#endif // DATABASEMANAGER_H
