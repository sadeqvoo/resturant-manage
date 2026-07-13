#ifndef CUSTOMERDAO_H
#define CUSTOMERDAO_H

#include "../sqlite3.h"
#include <string>
#include <memory>
#include <map>

#include "../models/customer.h" 

class CustomerDAO {
private:
    sqlite3* db;

public:
    CustomerDAO(sqlite3* databasePointer);
    ~CustomerDAO() = default;

    
    int registerCustomer(const std::string& username);
    bool updateCustomerLoyalty(int customerId, int newPoints, const std::string& newLevel);
    
    std::map<std::string, int> getUserLevelStats();

    std::shared_ptr<customer> getCustomerById(int customerId);
};

#endif