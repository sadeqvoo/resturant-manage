#ifndef RESTAURANTDAO_H
#define RESTAURANTDAO_H

#include "../sqlite3.h"
#include "../models/restaurant.h"
#include <vector>
#include <memory>
#include <string>

class RestaurantDAO {
private:
    sqlite3* db;

public:
    RestaurantDAO(sqlite3* databasePointer);
    ~RestaurantDAO() = default;

    bool insertRestaurant(std::shared_ptr<restaurant> res);

    bool deleteRestaurant(int restaurantID);

    std::vector<std::shared_ptr<restaurant>> getAllRestaurants();
    bool updateRestaurantStatus(int restaurantID, int status) ; 
};

#endif 