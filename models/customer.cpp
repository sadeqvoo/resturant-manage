#include <iostream>
#include "customer.h"


customer::customer(int id1 , int points1 , std::string membership_level1 , cart myCart1 ,std::vector<order> orderHistory1 , std::string rolename1):
id(id1) ,points(points1) ,membership_level(membership_level1) ,myCart(myCart1) ,orderHistory(orderHistory1), user(rolename1) {}

void customer::addOrderToHistory(const order& newOrder) 
{
    orderHistory.push_back(newOrder);
}

void customer::displayOrderHistory() const 
{
    std::cout << "\n--- ORDER HISTORY ---" << std::endl;
    if (orderHistory.empty()) {
        std::cout << "You haven't placed any orders yet.\n" << std::endl;
        return;
    }
    
    for (size_t i = 0; i < orderHistory.size(); i++) {
        std::cout << "Order #" << orderHistory[i].getID() 
                  << " | Total: " << orderHistory[i].gettotalAmount() << " Toman"
                  << " | Status: " << orderHistory[i].getStatusString() << std::endl;
    }
    std::cout << "---------------------\n" << std::endl;
}

void customer::displayProfile() const {
    std::cout << "\n--- Customer Profile ---" << std::endl;
    std::cout << "Customer ID: " << id << std::endl;
    std::cout << "Membership Level: " << membership_level << std::endl;
    std::cout << "Reward Points: " << points << std::endl;
    std::cout << "------------------------\n" << std::endl;
}