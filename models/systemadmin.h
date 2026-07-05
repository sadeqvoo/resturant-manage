#ifndef SYSTEMADMIN_H
#define SYSTEMADMIN_H

#include "user.h"
#include "restaurant.h"
#include <vector>
#include <memory>
#include <string>

class systemadmin : public user 
{
    private:
    std::vector<std::shared_ptr<restaurant>> allRestaurants;

    public:
    systemadmin(const std::string& rolename1);
    ~systemadmin() = default;

    void displayAllRestaurants() const;
    void addRestaurant(std::shared_ptr<restaurant> newRestaurant);
    void removeRestaurant(const std::string& restaurantName);

    void handleAdminMenu();

    std::vector<std::shared_ptr<restaurant>> getAllRestaurants() const { return allRestaurants; }
    
    void setRestaurants(const std::vector<std::shared_ptr<restaurant>>& restaurants) { allRestaurants = restaurants; }

};


#endif