#ifndef ORDERDAO_H
#define ORDERDAO_H

#include "../sqlite3.h"
#include "../models/order.h"
#include <vector>
#include <memory>
#include <string>
#include "MenuDAO.h"

class OrderDAO {
private:
    sqlite3* db;

public:
    OrderDAO(sqlite3* databasePointer);
    ~OrderDAO() = default;

    bool insertOrder(std::shared_ptr<order> newOrder , int customerId);

    bool updateOrderStatus(int orderID, int newStatus);
    
    std::vector<std::shared_ptr<order>> getOrdersForRestaurant(int restaurantID);

    std::vector<std::shared_ptr<order>> getAllOrdersForCustomer(int customerId);

    std::vector<std::shared_ptr<order>> getAllOrders();
};

#endif 