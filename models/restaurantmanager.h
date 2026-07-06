#ifndef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include "user.h"
#include <memory>
#include <vector>
#include "restaurant.h" 
#include "order.h"    
#include "food.h"  
#include "beverage.h"

class restaurantmanager : public user
{
    private:
    std::shared_ptr<restaurant> managedRestaurant ;
    std::vector<order> activeOrders ;

    public:
    restaurantmanager(std::shared_ptr<restaurant> targetRestaurant, const std::vector<order>& ordersFromDB , const std::string& rolename1);    

    void displayMenu() const;
    void addFoodItem(const std::string& id, const std::string& name, const std::string& desc, double price, int cookingTime);
    void addBeverageItem(const std::string& id, const std::string& name, const std::string& desc, double price, int volume) ;
    void removeMenuItem(const std::string& name);
    void updateItemPrice(const std::string& name, double newPrice);
    void updateItemDescription(const std::string& name, const std::string& newDesc);
    void updateItemAvailability(const std::string& name, bool available);

    void displayActiveOrders() const;
    void updateOrderStatus(int orderId, std::string newStatus);

    std::vector<order> getActiveOrders() const { return activeOrders; }
};


#endif