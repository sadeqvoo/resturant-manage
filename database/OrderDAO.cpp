#include "OrderDAO.h"
#include <iostream>
#include <string>


static int mainOrderCallback(void* data, int argc, char** argv, char** azColName) {
    auto* ordersList = static_cast<std::vector<std::shared_ptr<order>>*>(data);

   
    int orderID = argv[0] ? std::stoi(argv[0]) : 0;
    int restaurantID = argv[1] ? std::stoi(argv[1]) : 0;
    double totalAmount = argv[2] ? std::stod(argv[2]) : 0.0;
    int status = argv[3] ? std::stoi(argv[3]) : 0;

    auto newOrder = std::make_shared<order>(orderID, restaurantID, totalAmount, status);
    ordersList->push_back(newOrder);

    return 0;
}

static int orderItemsCallback(void* data, int argc, char** argv, char** azColName) {
    auto* currentOrder = static_cast<std::shared_ptr<order>*>(data);

    std::string itemName = argv[1] ? argv[1] : "";
    int quantity = argv[2] ? std::stoi(argv[2]) : 0;

    (*currentOrder)->addItem(itemName, quantity);

    return 0;
}

OrderDAO::OrderDAO(sqlite3* databasePointer) : db(databasePointer) {}

bool OrderDAO::insertOrder(std::shared_ptr<order> newOrder) {
    if (newOrder == nullptr) return false;
    
    char* messageError = nullptr;

    std::string sql_orders = "INSERT INTO orders (order_id, restaurant_id, total_amount, status) VALUES ("
                             + std::to_string(newOrder->getOrderID()) + ", "
                             + std::to_string(newOrder->getRestaurantID()) + ", "
                             + std::to_string(newOrder->getTotalPrice()) + ", 0);";

    int exit = sqlite3_exec(db, sql_orders.c_str(), NULL, 0, &messageError);
    
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert Main Order: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false; 
    }

    for (const auto& item : newOrder->getCartItems()) {
        std::string sql_items = "INSERT INTO order_items (order_id, item_name, quantity) VALUES ("
                                + std::to_string(newOrder->getOrderID()) + ", '"
                                + item.getName() + "', "
                                + std::to_string(item.getQuantity()) + ");";

        exit = sqlite3_exec(db, sql_items.c_str(), NULL, 0, &messageError);
        
        if (exit != SQLITE_OK) {
            std::cerr << "Error Insert Order Item (" << item.getName() << "): " << messageError << std::endl;
            sqlite3_free(messageError);
        }
    }

    std::cout << "Order #" << newOrder->getOrderID() << " saved successfully!" << std::endl;
    return true;
}

bool OrderDAO::updateOrderStatus(int orderID, int newStatus) {
    char* messageError = nullptr;

    std::string sql = "UPDATE orders SET status = " + std::to_string(newStatus) + 
                      " WHERE order_id = " + std::to_string(orderID) + ";";

    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    
    if (exit != SQLITE_OK) {
        std::cerr << "Error Update Order Status: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    } else {
        std::cout << "Order status updated to " << newStatus << "!" << std::endl;
        return true;
    }
}

std::vector<std::shared_ptr<order>> OrderDAO::getOrdersForRestaurant(int restaurantID) {
    std::vector<std::shared_ptr<order>> ordersList;
    char* messageError = nullptr;

    std::string sql_select_orders = "SELECT * FROM orders WHERE restaurant_id = " + std::to_string(restaurantID) + ";";

    int exit = sqlite3_exec(db, sql_select_orders.c_str(), mainOrderCallback, &ordersList, &messageError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error Select Orders for Restaurant: " << messageError << std::endl;
        sqlite3_free(messageError);
        return ordersList;
    }

    for (auto& ord : ordersList) {
        std::string sql_select_items = "SELECT * FROM order_items WHERE order_id = " + std::to_string(ord->getOrderID()) + ";";

        exit = sqlite3_exec(db, sql_select_items.c_str(), orderItemsCallback, &ord, &messageError);

        if (exit != SQLITE_OK) {
            std::cerr << "Error Select Order Items for ID " << ord->getOrderID() << ": " << messageError << std::endl;
            sqlite3_free(messageError);
        }
    }

    return ordersList;
}

std::vector<std::shared_ptr<order>> OrderDAO::getAllOrdersForCustomer() {
    std::vector<std::shared_ptr<order>> ordersList;
    char* messageError = nullptr;

    std::string sql_select_all = "SELECT * FROM orders;";

    int exit = sqlite3_exec(db, sql_select_all.c_str(), mainOrderCallback, &ordersList, &messageError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error Select All Orders: " << messageError << std::endl;
        sqlite3_free(messageError);
        return ordersList;
    }

    for (auto& ord : ordersList) {
        std::string sql_select_items = "SELECT * FROM order_items WHERE order_id = " + std::to_string(ord->getOrderID()) + ";";

        exit = sqlite3_exec(db, sql_select_items.c_str(), orderItemsCallback, &ord, &messageError);

        if (exit != SQLITE_OK) {
            std::cerr << "Error Select Order Items for ID " << ord->getOrderID() << ": " << messageError << std::endl;
            sqlite3_free(messageError);
        }
    }

    return ordersList;
}