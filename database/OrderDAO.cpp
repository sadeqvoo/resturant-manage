#include "OrderDAO.h"
#include <iostream>
#include <string>


static int mainOrderCallback(void* data, int argc, char** argv, char** azColName) {
    auto* ordersList = static_cast<std::vector<std::shared_ptr<order>>*>(data);

    int orderID = 0;
    int restaurantID = 0;
    double totalAmount = 0.0;
    int status = 0;
    

    for (int i = 0; i < argc; i++) {
        if (argv[i] == nullptr) continue;
        std::string colName = azColName[i];

        if (colName == "order_id") {
            orderID = std::stoi(argv[i]);
        } 
        else if (colName == "restaurant_id") {
            restaurantID = std::stoi(argv[i]);
        } 
        else if (colName == "total_amount") {
            totalAmount = std::stod(argv[i]);
        } 
        else if (colName == "status") {
            status = std::stoi(argv[i]);
        }
        
    }

    auto newOrder = std::make_shared<order>(orderID, static_cast<OrderStatus>(status), restaurantID, cart{}, totalAmount);
    ordersList->push_back(newOrder);

    return 0;
}

static int orderItemsCallback(void* data, int argc, char** argv, char** azColName) {
    auto* currentOrder = static_cast<std::shared_ptr<order>*>(data);

    std::string itemName = argv[1] ? argv[1] : "";
    int quantity = argv[2] ? std::stoi(argv[2]) : 0;

    auto tempItem = std::make_shared<menuitem>(); 
    tempItem->setname(itemName); 
    
    (*currentOrder)->getorderItem().addtocart(tempItem, quantity);

    return 0;
}

OrderDAO::OrderDAO(sqlite3* databasePointer) : db(databasePointer) {}

bool OrderDAO::insertOrder(std::shared_ptr<order> newOrder , int customerId) {
    if (newOrder == nullptr) return false;
    
    char* messageError = nullptr;

    std::string sql_orders = "INSERT INTO orders (order_id, customer_id , restaurant_id, total_amount, status) VALUES ("
                             + std::to_string(newOrder->getID()) + ", "
                             + std::to_string(customerId) + ", "
                             + std::to_string(newOrder->getRestaurantID()) + ", "
                             + std::to_string(newOrder->gettotalAmount()) + ", 0);";

    int exit = sqlite3_exec(db, sql_orders.c_str(), NULL, 0, &messageError);
    
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert Main Order: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false; 
    }

    for (const auto& item : newOrder->getorderItem().getorderItem()) {
        std::string sql_items = "INSERT INTO order_items (order_id, item_name, quantity) VALUES ("
                                + std::to_string(newOrder->getID()) + ", '"
                                + item.item->getname() + "', "
                                + std::to_string(item.number) + ");";
    
        exit = sqlite3_exec(db, sql_items.c_str(), NULL, 0, &messageError);
        
        if (exit != SQLITE_OK) {
            std::cerr << "Error Insert Order Item (" << item.item->getname() << "): " << messageError << std::endl;
            sqlite3_free(messageError);
        }
    }

    std::cout << "Order #" << newOrder->getID() << " saved successfully!" << std::endl;
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
        std::string sql_select_items = "SELECT * FROM order_items WHERE order_id = " + std::to_string(ord->getID()) + ";";

        exit = sqlite3_exec(db, sql_select_items.c_str(), orderItemsCallback, &ord, &messageError);

        if (exit != SQLITE_OK) {
            std::cerr << "Error Select Order Items for ID " << ord->getID() << ": " << messageError << std::endl;
            sqlite3_free(messageError);
        }
    }

    return ordersList;
}

std::vector<std::shared_ptr<order>> OrderDAO::getAllOrdersForCustomer(int customerId) 
{
    std::vector<std::shared_ptr<order>> ordersList;
    char* messageError = nullptr;

    std::string sql_select_all = "SELECT * FROM orders WHERE customer_id =" + std::to_string(customerId) + ";";

    int exit = sqlite3_exec(db, sql_select_all.c_str(), mainOrderCallback, &ordersList, &messageError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error Select All Orders: " << messageError << std::endl;
        sqlite3_free(messageError);
        return ordersList;
    }

    for (auto& ord : ordersList) {
        std::string sql_select_items = "SELECT * FROM order_items WHERE order_id = " + std::to_string(ord->getID()) + ";";

        exit = sqlite3_exec(db, sql_select_items.c_str(), orderItemsCallback, &ord, &messageError);

        if (exit != SQLITE_OK) {
            std::cerr << "Error Select Order Items for ID " << ord->getID() << ": " << messageError << std::endl;
            sqlite3_free(messageError);
        }
    }

    return ordersList;
}

std::vector<std::shared_ptr<order>> OrderDAO::getAllOrders() {
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
        std::string sql_select_items = "SELECT * FROM order_items WHERE order_id = " + std::to_string(ord->getID()) + ";";
        sqlite3_exec(db, sql_select_items.c_str(), orderItemsCallback, &ord, &messageError);
    }

    return ordersList;
}