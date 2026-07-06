#include "restaurantmanager.h"
#include <iostream>

restaurantmanager::restaurantmanager(std::shared_ptr<restaurant> targetRestaurant, const std::vector<order>& ordersFromDB , const std::string& rolename1):
managedRestaurant(targetRestaurant) , activeOrders(ordersFromDB) , user(rolename1) {}

void restaurantmanager::displayMenu() const
{
    if (managedRestaurant == nullptr) {
        std::cout << "\n[Manager] No restaurant is currently assigned!\n";
        return;
    }
    std::cout << "\n=========================================\n";
    std::cout << "   Management Menu of: " << managedRestaurant->getname() << std::endl;
    std::cout << "=========================================\n";
    
    managedRestaurant->displayMenu();
}

void restaurantmanager::addFoodItem(const std::string& id, const std::string& name, const std::string& desc, double price, int cookingTime)
{
    if (managedRestaurant == nullptr) return;
    auto newFood = std::make_shared<food>(id, name, desc, price, true, cookingTime);
    managedRestaurant->addItemToMenu(newFood);
    std::cout << "\n[Manager] Food item '" << name << "' successfully added to the menu.\n";
}

void restaurantmanager::addBeverageItem(const std::string& id, const std::string& name, const std::string& desc, double price, int volume) {
    if (managedRestaurant == nullptr) return;

    auto newBeverage = std::make_shared<beverage>(id, name, desc, price, true, volume);
    
    managedRestaurant->addItemToMenu(newBeverage);
    std::cout << "\n[Manager] Beverage item '" << name << "' successfully added to the menu.\n";
}

void restaurantmanager::removeMenuItem(const std::string& name)
{
    if (managedRestaurant == nullptr) return;

    auto& menu = managedRestaurant->getMenu();
    for (size_t i = 0; i < menu.size(); ++i) {
        if (menu[i] != nullptr && menu[i]->getname() == name) {
            managedRestaurant->removeItemFromMenu(menu[i]->getID());
            std::cout << "\n[Manager] '" << name << "' has been permanently removed from the menu.\n";
            return;
        }
    }
    std::cout << "\n[Manager] Item '" << name << "' not found in the menu!\n";
}

void restaurantmanager::updateItemPrice(const std::string& name, double newPrice)
{
    if (managedRestaurant == nullptr) return;

    auto& menu = managedRestaurant->getMenu();
    for (size_t i = 0; i < menu.size(); ++i) {
        if (menu[i] != nullptr && menu[i]->getname() == name) {
            menu[i]->setbaseprice(newPrice); 
            std::cout << "\n[Manager] Price of '" << name << "' updated to " << newPrice << " Toman.\n";
            return;
        }
    }
    std::cout << "\n[Manager] Item not found for price update!\n";
}

void restaurantmanager::updateItemDescription(const std::string& name, const std::string& newDesc)
{
    if (managedRestaurant == nullptr) return;
    auto& menu = managedRestaurant->getMenu();

    for (size_t i = 0; i < menu.size(); ++i) {
        if (menu[i] != nullptr && menu[i]->getname() == name) {
            menu[i]->setdescription(newDesc); 
            std::cout << "\n[Manager] descripsion '" << name << "' updated " << ".\n";
            return;
        }
    }
    std::cout << "\n[Manager] Item not found for description update!\n";

}
void restaurantmanager::updateItemAvailability(const std::string& name, bool available)
{
    if (managedRestaurant == nullptr) return;

    auto& menu = managedRestaurant->getMenu();
    for (size_t i = 0; i < menu.size(); ++i) {
        if (menu[i] != nullptr && menu[i]->getname() == name) {
            menu[i]->setisAvailable(available); 
            std::cout << "\n[Manager] Availability of '" << name << "' updated to " 
                      << (available ? "Available" : "Sold Out") << ".\n";
            return;
        }
    }
    std::cout << "\n[Manager] Item not found for availability update!\n";
}

void restaurantmanager::displayActiveOrders() const
{
    if (activeOrders.empty()) {
        std::cout << "\n[Manager] No active orders to prepare for this restaurant.\n";
        return;
    }

    std::cout << "\n--- CURRENT ACTIVE ORDERS ---\n";
    for (size_t i = 0; i < activeOrders.size(); ++i) {
        std::cout << "Order ID: " << activeOrders[i].getID() 
                  << "  Total Amount: " << activeOrders[i].gettotalAmount() << " Toman"
                  << "  Status: " << activeOrders[i].getStatusString() << "\n";
        
        std::cout << "  Items to Prepare:\n";
        
    auto items = activeOrders[i].getorderItem().getorderItem();
        for (size_t j = 0; j < items.size(); ++j) {
            if (items[j].item != nullptr) {
                std::cout << "    - " << items[j].item->getname() << "  [Quantity: " << items[j].number << "]\n";
            }
        }
        std::cout << "-----------------------------------------\n";
    }
}
void restaurantmanager::updateOrderStatus(int orderId, std::string newStatus)
{
    for (size_t i = 0; i < activeOrders.size(); ++i) {
        if (activeOrders[i].getID() == orderId) 
        {
            activeOrders[i].setStatus(newStatus); 
            
            std::cout << "\n[Manager] Order " << orderId << " status successfully changed in system.\n";
            return;
        }
    }
    std::cout << "\n[Manager] Order ID " << orderId << " not found in active list!\n";
}

