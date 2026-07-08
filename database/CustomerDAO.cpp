#include "CustomerDAO.h"
#include <iostream>

CustomerDAO::CustomerDAO(sqlite3* databasePointer) : db(databasePointer) {}

bool CustomerDAO::registerCustomer(const std::string& username) {
    char* messageError = nullptr;
    // هنگام ثبت‌نام، نیازی به دادن امتیاز و سطح نیست، خود دیتابیس مقادیر پیش‌فرض را می‌گذارد
    std::string sql = "INSERT INTO customers (username) VALUES ('" + username + "');";
    
    if (sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError) != SQLITE_OK) {
        std::cerr << "Error Registering Customer: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    }
    std::cout << "Customer registered successfully! (Default Level: Normal, Points: 0)" << std::endl;
    return true;
}

static int customerCallback(void* data, int argc, char** argv, char** azColName) {
    auto* foundCustomer = static_cast<std::shared_ptr<customer>*>(data);
    
    int id = argv[0] ? std::stoi(argv[0]) : 0;
    std::string username = argv[1] ? argv[1] : "";
    int points = argv[2] ? std::stoi(argv[2]) : 0;
    std::string level = argv[3] ? argv[3] : "";

    
    *foundCustomer = std::make_shared<customer>(id, username, points, level);
    return 0;
}

std::shared_ptr<customer> CustomerDAO::getCustomerById(int customerId) {
    std::shared_ptr<customer> foundCustomer = nullptr;
    char* messageError = nullptr;
    std::string sql = "SELECT * FROM customers WHERE id = " + std::to_string(customerId) + ";";
    
    sqlite3_exec(db, sql.c_str(), customerCallback, &foundCustomer, &messageError);
    return foundCustomer;
}