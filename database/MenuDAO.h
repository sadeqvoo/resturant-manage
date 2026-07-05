#ifndef MENUDAO_H
#define MENUDAO_H

#include "../sqlite3.h"
#include "../models/menuitem.h"
#include "../models/food.h"
#include "../models/beverage.h"
#include <vector>
#include <memory>
#include <string>


class MenuDAO {
private:
    sqlite3* db; 

public:
    MenuDAO(sqlite3* databasePointer);
    ~MenuDAO() = default;

    bool insertMenuItem(std::shared_ptr<menuitem> item, int restaurantID);

    bool deleteMenuItem(const std::string& itemID);

    std::vector<std::shared_ptr<menuitem>> getMenuForRestaurant(int restaurantID);
};

#endif // MENUDAO_H