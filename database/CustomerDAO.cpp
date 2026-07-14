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


static int statsCallback(void* data, int argc, char** argv, char** azColName) {
    auto* stats = static_cast<std::map<std::string, int>*>(data);
    if (argc == 2 && argv[0] && argv[1]) {
        std::string levelName = argv[0];
        int count = std::stoi(argv[1]);
        (*stats)[levelName] = count;
    }
    return 0;
}

std::map<std::string, int> CustomerDAO::getUserLevelStats() {
    std::map<std::string, int> stats;
    char* messageError = nullptr;
    
    std::string sql = "SELECT current_level, COUNT(*) FROM customers GROUP BY current_level;";
    
    sqlite3_exec(db, sql.c_str(), statsCallback, &stats, &messageError);
    return stats;
}


bool CustomerDAO::logLevelChange(int customerId, const std::string& oldLevel, const std::string& newLevel, const std::string& reason) {
    char* messageError = nullptr;
    std::string sql = "INSERT INTO level_logs (customer_id, old_level, new_level, reason) VALUES ("
                    + std::to_string(customerId) + ", '"
                    + oldLevel + "', '"
                    + newLevel + "', '"
                    + reason + "');";
    
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error logging level change: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    }
    return true;
}

static int logsCallback(void* data, int argc, char** argv, char** azColName) {
    std::cout << ">> Log ID: " << (argv[0] ? argv[0] : "N/A") 
              << " | Customer ID: " << (argv[1] ? argv[1] : "N/A")
              << " | Level Change: [" << (argv[2] ? argv[2] : "N/A") << " -> " << (argv[3] ? argv[3] : "N/A") << "]"
              << " | Date: " << (argv[4] ? argv[4] : "N/A")
              << " | Reason: " << (argv[5] ? argv[5] : "N/A") << std::endl;
    return 0;
}

void CustomerDAO::displayLevelLogs() {
    char* messageError = nullptr;
    std::string sql = "SELECT log_id, customer_id, old_level, new_level, change_date, reason FROM level_logs ORDER BY change_date DESC;";
    
    std::cout << "\n=========================================" << std::endl;
    std::cout << "        User Level Changes History       " << std::endl;
    std::cout << "=========================================" << std::endl;
    
    int exit = sqlite3_exec(db, sql.c_str(), logsCallback, NULL, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error reading level logs: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    std::cout << "=========================================\n" << std::endl;
}


static int couponsCallback(void* data, int argc, char** argv, char** azColName) {
    auto* couponsList = static_cast<std::vector<Coupon>*>(data);
    Coupon cp;
    cp.id = argv[0] ? std::stoi(argv[0]) : 0;
    cp.code = argv[1] ? argv[1] : "";
    cp.discountPercent = argv[2] ? std::stod(argv[2]) : 0.0;
    cp.isUsed = argv[3] ? (std::stoi(argv[3]) == 1) : false;
    couponsList->push_back(cp);
    return 0;
}

bool CustomerDAO::generateCouponsForUser(int customerId, const std::string& levelName) {
    int count = 0;
    double discount = 0.0;
    std::string codePrefix = "";

    if (levelName == "Silver") {
        count = 1;
        discount = 10.0; // ۱۰ درصد تخفیف
        codePrefix = "SILVER";
    } else if (levelName == "Gold") {
        count = 2;
        discount = 15.0; // ۱۵ درصد تخفیف
        codePrefix = "GOLD";
    } else if (levelName == "VIP") {
        count = 3;
        discount = 20.0; // ۲۰ درصد تخفیف
        codePrefix = "VIP";
    } else {
        return false; // سطح نرمال کوپنی دریافت نمی‌کند
    }

    char* messageError = nullptr;
    for (int i = 1; i <= count; ++i) {
        // ساخت یک کد تصادفی مثل VIP5839
        std::string code = codePrefix + std::to_string(rand() % 9000 + 1000); 
        std::string sql = "INSERT INTO coupons (customer_id, code, discount_percent) VALUES ("
                        + std::to_string(customerId) + ", '" + code + "', " + std::to_string(discount) + ");";
        
        int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error generating coupon: " << messageError << std::endl;
            sqlite3_free(messageError);
            return false;
        }
    }
    return true;
}

// دریافت لیست کوپن‌های فعال کاربر
std::vector<Coupon> CustomerDAO::getUnusedCoupons(int customerId) {
    std::vector<Coupon> couponsList;
    char* messageError = nullptr;
    std::string sql = "SELECT id, code, discount_percent, is_used FROM coupons WHERE customer_id = " 
                    + std::to_string(customerId) + " AND is_used = 0;";
    
    int exit = sqlite3_exec(db, sql.c_str(), couponsCallback, &couponsList, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error getting coupons: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    return couponsList;
}

// باطل کردن کوپن پس از مصرف
bool CustomerDAO::markCouponAsUsed(int customerId, const std::string& code) {
    char* messageError = nullptr;
    std::string sql = "UPDATE coupons SET is_used = 1 WHERE customer_id = " 
                    + std::to_string(customerId) + " AND code = '" + code + "';";
    
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error updating coupon status: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    }
    return true;
}