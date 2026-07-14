#ifndef CUSTOMERDAO_H
#define CUSTOMERDAO_H

#include "../sqlite3.h"
#include <string>
#include <memory>
#include <map>

#include "../models/customer.h" 


struct Coupon 
{
    int id;
    std::string code;
    double discountPercent;
    bool isUsed;
};



class CustomerDAO {
private:
    sqlite3* db;

public:
    CustomerDAO(sqlite3* databasePointer);
    ~CustomerDAO() = default;



    bool generateCouponsForUser(int customerId, const std::string& levelName);
    std::vector<Coupon> getUnusedCoupons(int customerId);
    bool markCouponAsUsed(int customerId, const std::string& code);
    
    int registerCustomer(const std::string& username);
    bool updateCustomerLoyalty(int customerId, int newPoints, const std::string& newLevel);
    
    bool logLevelChange(int customerId, const std::string& oldLevel, const std::string& newLevel, const std::string& reason);
    void displayLevelLogs();

    std::map<std::string, int> getUserLevelStats();

    std::shared_ptr<customer> getCustomerById(int customerId);
};

#endif