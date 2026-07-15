#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager() : db(nullptr) {}

DatabaseManager::~DatabaseManager() 
{
    closeDatabase();
}

bool DatabaseManager::openDatabase(const std::string& dbName) 
{
    int exit = sqlite3_open(dbName.c_str(), &db);
    
    if (exit) { 
        std::cerr << "Error open DB: " << sqlite3_errmsg(db) << std::endl; 
        return false;
    } else { 
        std::cout << "Opened Database Successfully!" << std::endl; 
        
        createTables();
        return true;
    }
}

void DatabaseManager::closeDatabase() {
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
}

void DatabaseManager::createTables() {
    char* messageError = nullptr;


    std::string sql_restaurants = 
        "CREATE TABLE IF NOT EXISTS restaurants ("
        "id INTEGER PRIMARY KEY, "
        "name TEXT, "
        "address TEXT, "
        "is_active INTEGER, "
        "preparation_time INTEGER, "
        "phone TEXT);";

    std::string sql_menu_items = 
        "CREATE TABLE IF NOT EXISTS menu_items ("
        "id TEXT PRIMARY KEY, "
        "restaurant_id INTEGER, "
        "name TEXT, "
        "description TEXT, "
        "price REAL, "
        "is_available INTEGER, "
        "item_type TEXT, "
        "extra_attribute INTEGER);";

    std::string sql_orders = 
        "CREATE TABLE IF NOT EXISTS orders ("
        "order_id INTEGER PRIMARY KEY, "
        "customer_id INTEGER, "
        "restaurant_id INTEGER, "
        "total_amount REAL, "
        "status INTEGER,"
        "order_date DATETIME DEFAULT (datetime('now', 'localtime')), "
        "FOREIGN KEY(customer_id) REFERENCES customers(id));";

    std::string sql_order_items = 
        "CREATE TABLE IF NOT EXISTS order_items ("
        "order_id INTEGER, "
        "item_name TEXT, "
        "quantity INTEGER);";

        
    std::string sql_customers = 
        "CREATE TABLE IF NOT EXISTS customers ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL, "
        "role TEXT NOT NULL, "            
        "points INTEGER DEFAULT 0, "        
        "current_level TEXT DEFAULT 'Normal');"; 

        std::string sql_level_logs = 
        "CREATE TABLE IF NOT EXISTS level_logs ("
        "log_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "customer_id INTEGER, "
        "old_level TEXT, "
        "new_level TEXT, "
        "change_date DATETIME DEFAULT (datetime('now', 'localtime')), "
        "reason TEXT, "
        "FOREIGN KEY(customer_id) REFERENCES customers(id));";


        std::string sql_coupons = 
        "CREATE TABLE IF NOT EXISTS coupons ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "customer_id INTEGER, "
        "code TEXT NOT NULL, "
        "discount_percent REAL, "
        "is_used INTEGER DEFAULT 0, "
        "FOREIGN KEY(customer_id) REFERENCES customers(id));";

    
    
    int exit = sqlite3_exec(db, sql_restaurants.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Create Restaurants Table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }

    exit = sqlite3_exec(db, sql_menu_items.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Create Menu Items Table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }

    exit = sqlite3_exec(db, sql_orders.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Create Orders Table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }

    exit = sqlite3_exec(db, sql_order_items.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Create Order Items Table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    
    exit = sqlite3_exec(db, sql_customers.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Create Restaurants Table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }

    exit = sqlite3_exec(db, sql_level_logs.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Create level_logs Table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }

    exit = sqlite3_exec(db, sql_coupons.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Create Coupons Table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }



    std::cout << "All Tables Checked/Created successfully!" << std::endl;
}