#include "RestaurantDAO.h"
#include <iostream>
#include <string>

RestaurantDAO::RestaurantDAO(sqlite3* databasePointer) : db(databasePointer) {}

bool RestaurantDAO::insertRestaurant(std::shared_ptr<restaurant> res) {
    if (res == nullptr) return false;

    char* messageError = nullptr;
    int activeInt = res->getisActive() ? 1 : 0; 

    std::string sql = "INSERT INTO restaurants (id, name, address, is_active, preparation_time, phone) VALUES ("
                      + std::to_string(res->getID()) + ", '"
                      + res->getname() + "', '"
                      + res->getaddress() + "', "
                      + std::to_string(activeInt) + ", "
                      + std::to_string(res->getpreparationTime()) + ", '"
                      + res->getphonenumber() + "');";

    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert Restaurant: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    } else {
        std::cout << "Restaurant record created successfully!" << std::endl;
        return true;
    }
}

bool RestaurantDAO::deleteRestaurant(int restaurantID) {
    char* messageError = nullptr;

    std::string sql = "DELETE FROM restaurants WHERE id = " + std::to_string(restaurantID) + ";";

    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    
    if (exit != SQLITE_OK) {
        std::cerr << "Error Delete Restaurant: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    } else {
        std::cout << "Restaurant deleted successfully!" << std::endl;
        return true;
    }
}

static int restaurantCallback(void* data, int argc, char** argv, char** azColName) {
    auto* restaurantsList = static_cast<std::vector<std::shared_ptr<restaurant>>*>(data);

    int id = argv[0] ? std::stoi(argv[0]) : 0;
    std::string name = argv[1] ? argv[1] : "";
    std::string address = argv[2] ? argv[2] : "";
    
    int activeNum = argv[3] ? std::stoi(argv[3]) : 0;
    bool isActive = (activeNum == 1);

    int prepTime = argv[4] ? std::stoi(argv[4]) : 0;
    std::string phone = argv[5] ? argv[5] : "";

    auto newRes = std::make_shared<restaurant>(id, name, address, isActive, prepTime, phone , "");
    restaurantsList->push_back(newRes);

    return 0;
}

std::vector<std::shared_ptr<restaurant>> RestaurantDAO::getAllRestaurants() 
{
    std::vector<std::shared_ptr<restaurant>> restaurantsList;
    char* messageError = nullptr;

    std::string sql_select = "SELECT * FROM restaurants;";

    int exit = sqlite3_exec(db, sql_select.c_str(), restaurantCallback, &restaurantsList, &messageError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error Select Restaurants: " << messageError << std::endl;
        sqlite3_free(messageError);
    }

    return restaurantsList;
}


bool RestaurantDAO::updateRestaurantStatus(int restaurantID, int status) 
{
    char* messageError = nullptr;

    std::string sql = "UPDATE restaurants SET is_active = " + std::to_string(status) + 
                      " WHERE id = " + std::to_string(restaurantID) + ";";

    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    
    if (exit != SQLITE_OK) {
        std::cerr << "Error Update Restaurant Status: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    } else {
        std::cout << "Restaurant status updated successfully!" << std::endl;
        return true;
    }
}