#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "../sqlite3.h" 
#include "restaurant.h"
#include <string>
#include <vector>
#include <memory>

class DatabaseManager {
private:
    sqlite3* db;
    bool executeSQL(const std::string& sql);

public:
    DatabaseManager();
    ~DatabaseManager();

    bool openDatabase(const std::string& dbName);
    void closeDatabase();
    void createTables();

sqlite3* getDatabasePointer() const { return db; }     
};

#endif 