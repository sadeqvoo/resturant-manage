#ifndef CUSTOMERDAO_H
#define CUSTOMERDAO_H

#include "../sqlite3.h"
#include <string>
#include <memory>

#include "../models/customer.h" 

class CustomerDAO {
private:
    sqlite3* db;

public:
    CustomerDAO(sqlite3* databasePointer);
    ~CustomerDAO() = default;

    
    bool registerCustomer(const std::string& username);
    
    
    std::shared_ptr<customer> getCustomerById(int customerId);
};

#endif