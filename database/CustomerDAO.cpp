#include "CustomerDAO.h"
#include <iostream>

CustomerDAO::CustomerDAO(sqlite3* databasePointer) : db(databasePointer) {}

int CustomerDAO::registerCustomer(const std::string& username) {
    char* messageError = nullptr;
    
    std::string sql = "INSERT INTO customers (username, role) VALUES ('" + username + "', 'Customer');";
    
    if (sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError) != SQLITE_OK) {
        std::cerr << "Error Registering Customer: " << messageError << std::endl;
        sqlite3_free(messageError);
        return -1;
    }
    std::cout << "Customer registered successfully! (Default Level: Normal, Points: 0)" << std::endl;

    int newlyGeneratedId = sqlite3_last_insert_rowid(db);
    return newlyGeneratedId;
}

static int customerCallback(void* data, int argc, char** argv, char** azColName) {
    auto* foundCustomer = static_cast<std::shared_ptr<customer>*>(data);
    
    int id = 0;
    std::string username = "";
    int points = 0;
    std::string level = "Normal";

    for (int i = 0; i < argc; i++) {
        if (argv[i] == nullptr) continue;
        std::string colName = azColName[i];
        
        if (colName == "id") id = std::stoi(argv[i]);
        else if (colName == "username") username = argv[i];
        else if (colName == "points") points = std::stoi(argv[i]);
        else if (colName == "current_level") level = argv[i];
    }
    
    *foundCustomer = std::make_shared<customer>(id, username, points, level);
    return 0;
}

std::shared_ptr<customer> CustomerDAO::getCustomerById(int customerId) {
    std::shared_ptr<customer> foundCustomer = nullptr;
    char* messageError = nullptr;
    std::string sql = "SELECT id, username, points, current_level FROM customers WHERE id = " + std::to_string(customerId) + ";";    
    sqlite3_exec(db, sql.c_str(), customerCallback, &foundCustomer, &messageError);
    return foundCustomer;
}

bool CustomerDAO::updateCustomerLoyalty(int customerId, int newPoints, const std::string& newLevel) {
    char* messageError = nullptr;
    
    std::string sql = "UPDATE customers SET points = " + std::to_string(newPoints) + 
                      ", current_level = '" + newLevel + "' WHERE id = " + std::to_string(customerId) + ";";
    
    if (sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError) != SQLITE_OK) {
        std::cerr << "Error Updating Customer Loyalty: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    }
    
    return true;
}