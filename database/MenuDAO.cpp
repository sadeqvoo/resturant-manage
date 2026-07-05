#include "MenuDAO.h"
#include <iostream>

MenuDAO::MenuDAO(sqlite3* databasePointer) : db(databasePointer) {}

getprice
bool MenuDAO::insertMenuItem(std::shared_ptr<menuitem> item, int restaurantID) {
    if (item == nullptr) return false;

    char* messageError = nullptr;
    int availableInt = item->getisAvailable() ? 1 : 0;
    
    std::string itemType = "";
    int extraAttr = 0;

    if (auto f = std::dynamic_pointer_cast<food>(item)) {
        itemType = "Food";
        extraAttr = f->getcookingTime(); 
    } 
    else if (auto b = std::dynamic_pointer_cast<beverage>(item)) {
        itemType = "Beverage";
        extraAttr = b->getVolume(); 
    }

    std::string sql = "INSERT INTO menu_items (id, restaurant_id, name, description, price, is_available, item_type, extra_attribute) VALUES ('"
                      + item->getID() + "', "
                      + std::to_string(restaurantID) + ", '"
                      + item->getname() + "', '"
                      + item->getdescription() + "', "
                      + std::to_string(item->getbaseprice()) + ", "
                      + std::to_string(availableInt) + ", '"
                      + itemType + "', "
                      + std::to_string(extraAttr) + ");";

    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert Menu Item: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    } else {
        std::cout << "Menu item '" << item->getname() << "' created successfully!" << std::endl;
        return true;
    }
}

bool MenuDAO::deleteMenuItem(const std::string& itemID) {
    char* messageError = nullptr;

    std::string sql = "DELETE FROM menu_items WHERE id = '" + itemID + "';";

    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    
    if (exit != SQLITE_OK) {
        std::cerr << "Error Delete Menu Item: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    } else {
        std::cout << "Menu item deleted successfully!" << std::endl;
        return true;
    }
}

static int menuCallback(void* data, int argc, char** argv, char** azColName) {
    auto* menuList = static_cast<std::vector<std::shared_ptr<menuitem>>*>(data);

    std::string id = argv[0] ? argv[0] : "";
    std::string name = argv[2] ? argv[2] : "";
    std::string description = argv[3] ? argv[3] : "";
    double price = argv[4] ? std::stod(argv[4]) : 0.0;
    
    int availNum = argv[5] ? std::stoi(argv[5]) : 0;
    bool isAvailable = (availNum == 1);
    
    std::string itemType = argv[6] ? argv[6] : "";
    int extraAttr = argv[7] ? std::stoi(argv[7]) : 0;

    if (itemType == "Food") {
        auto newFood = std::make_shared<food>(id, name, description, price, isAvailable, extraAttr);
        menuList->push_back(newFood);
    } 
    else if (itemType == "Beverage") {
        auto newBeverage = std::make_shared<beverage>(id, name, description, price, isAvailable, extraAttr);
        menuList->push_back(newBeverage);
    }

    return 0;
}

std::vector<std::shared_ptr<menuitem>> MenuDAO::getMenuForRestaurant(int restaurantID) {
    std::vector<std::shared_ptr<menuitem>> menuList;
    char* messageError = nullptr;

    std::string sql_select = "SELECT * FROM menu_items WHERE restaurant_id = " + std::to_string(restaurantID) + ";";

    int exit = sqlite3_exec(db, sql_select.c_str(), menuCallback, &menuList, &messageError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error Select Menu Items: " << messageError << std::endl;
        sqlite3_free(messageError);
    }

    return menuList;
}