#include "DatabaseManager.hpp"
#include <iostream>
#include <sqlite3.h>
#include <tuple>

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
                      "wins INTEGER DEFAULT 0,"
                      "losses INTEGER DEFAULT 0);";

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

bool DatabaseManager::authenticatePlayer(const std::string& username, const std::string& password) {

    std::string sql = "SELECT * FROM players WHERE username = ? AND password = ?;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    int result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    // Si se encuentra una fila, significa que el usuario fue autenticado correctamente
    return result == SQLITE_ROW;
}

bool DatabaseManager::registerPlayer(const std::string& username, const std::string& password) {

    std::string sql = "SELECT * FROM players WHERE username = ?;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    int result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    // Si se encuentra una fila, significa que ya existe un usuario con ese nombre de usuario
    if (result == SQLITE_ROW) {
        return false; // No se puede registrar el usuario porque el nombre de usuario ya existe
    }

    // Intenta agregar el nuevo usuario a la base de datos
    addPlayer(username, password);

    return true; // Usuario registrado con éxito
}

std::tuple<int, int> DatabaseManager::getPlayerWinLossRecord(const std::string& username) {
    
    const char* sql = "SELECT wins, losses FROM players WHERE username = ?";

    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (result != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return std::make_tuple(-1, -1); // Indicar error con valores negativos
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);

    if (result == SQLITE_ROW) {
        int wins = sqlite3_column_int(stmt, 0);
        int losses = sqlite3_column_int(stmt, 1);
        sqlite3_finalize(stmt);
        return std::make_tuple(wins, losses);
    } else if (result == SQLITE_DONE) {
        std::cerr << "No record found for username: " << username << std::endl;
        sqlite3_finalize(stmt);
        return std::make_tuple(-1, -1); // Indicar que no se encontraron registros
    } else {
        std::cerr << "Error executing query: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return std::make_tuple(-1, -1); // Indicar error con valores negativos
    }
}

void DatabaseManager::incrementPlayerWins(const std::string& username) {
    const char* sql = "UPDATE players SET wins = wins + 1 WHERE username = ?;";

    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (result != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);

    if (result != SQLITE_DONE) {
        std::cerr << "Error updating wins: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

void DatabaseManager::incrementPlayerLosses(const std::string& username) {
    const char* sql = "UPDATE players SET losses = losses + 1 WHERE username = ?;";

    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (result != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);

    if (result != SQLITE_DONE) {
        std::cerr << "Error updating losses: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
