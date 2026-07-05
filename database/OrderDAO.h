#ifndef ORDERDAO_H
#define ORDERDAO_H

#include "../sqlite3.h"
#include "../models/order.h"
#include <vector>
#include <memory>
#include <string>

class OrderDAO {
private:
    sqlite3* db;

public:
    OrderDAO(sqlite3* databasePointer);
    ~OrderDAO() = default;

    bool insertOrder(std::shared_ptr<order> newOrder);

    bool updateOrderStatus(int orderID, int newStatus);
    
    std::vector<std::shared_ptr<order>> getOrdersForRestaurant(int restaurantID);

    std::vector<std::shared_ptr<order>> getAllOrdersForCustomer();
};

#endif 