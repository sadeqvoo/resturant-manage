
#include "user.h"
#include <memory>
#include <vector>
#include "restaurant.h" 
#include "order.h"      

class restaurantmanager : public user
{
    private:
    std::shared_ptr<restaurant> managedRestaurant ;
    std::vector<order> activeOrders ;

    public:
    restaurantmanager(std::shared_ptr<Restaurant> targetRestaurant, const std::vector<Order>& ordersFromDB , const std::string& rolename1);    

    void displayMenu() const;
    void addMenuItem(const std::string& name, double price, const std::string& desc);
    void removeMenuItem(const std::string& name);
    void updateItemPrice(const std::string& name, double newPrice);
    void updateItemDescription(const std::string& name, const std::string& newDesc);
    void updateItemAvailability(const std::string& name, bool available);

    void displayActiveOrders() const;
    void updateOrderStatus(int orderId, int newStatus);

    std::vector<Order> getActiveOrders() const { return activeOrders; }
};


#endif