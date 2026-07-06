#include "systemadmin.h"
#include <iostream>
#include <string>

systemadmin::systemadmin(const std::string& rolename1) 
    : user(rolename1) {}

void systemadmin::displayAllRestaurants() const {
    std::cout << "\n--- REGISTERED RESTAURANTS ---\n";
    if (allRestaurants.empty()) {
        std::cout << "No restaurants registered in the system yet.\n";
        return;
    }

    for (size_t i = 0; i < allRestaurants.size(); ++i) {
        if (allRestaurants[i] != nullptr) {
            std::cout << i + 1 << ". Name: " << allRestaurants[i]->getname() << "\n";
        }
    }
    std::cout << "------------------------------\n";
}

void systemadmin::addRestaurant(std::shared_ptr<restaurant> newRestaurant) {
    if (newRestaurant == nullptr) return;
    
    allRestaurants.push_back(newRestaurant);
    std::cout << "\n[System Admin] Restaurant '" << newRestaurant->getname() << "' successfully added to the system.\n";
}

void systemadmin::removeRestaurant(const std::string& restaurantName) {
    for (size_t i = 0; i < allRestaurants.size(); ++i) {
        if (allRestaurants[i] != nullptr && allRestaurants[i]->getname() == restaurantName) {
            allRestaurants.erase(allRestaurants.begin() + i);
            std::cout << "\n[System Admin] Restaurant '" << restaurantName << "' has been removed from the system.\n";
            return;
        }
    }
    std::cout << "\n[System Admin] Restaurant '" << restaurantName << "' not found!\n";
}

void systemadmin::handleAdminMenu() {
    int choice = 0;
    while (true) {
        std::cout << "\033[2J\033[H";
        std::cout << "===== SYSTEM ADMIN PANEL =====" << std::endl;
        std::cout << "1. Display All Restaurants" << std::endl;
        std::cout << "2. Add New Restaurant" << std::endl;
        std::cout << "3. Remove Restaurant" << std::endl;
        std::cout << "4. Logout / Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "\033[2J\033[H";
            displayAllRestaurants();
            std::cout << "\nPress Enter to return...";
            std::cin.ignore();
            std::cin.get();
        }
        else if (choice == 2) {
            std::cout << "\033[2J\033[H";
            int id;
            std::string name, address;
            
            std::cout << "\n--- Enter Restaurant Details ---\n";
            std::cout << "Enter Restaurant ID (Number): ";
            std::cin >> id;
            
            std::cout << "Enter Restaurant Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            
            std::cout << "Enter Restaurant Address: ";
            std::getline(std::cin, address);

            bool isActive ;
            std::cout << "Enter Restaurant Active: y/n ? " ;
            std::string a ;
            std::cin>> a; 
            if (a == "y") isActive = true ;
            else isActive = false ;

            int preparationTime ;
            std::cout << "Enter Restaurant preparation Time :" ;
            std::cin >> preparationTime ;

            std::string phonenumber1 ;
            std::cout << "Enter Restaurant Phonenumber : " ;
            std::cin >> phonenumber1 ;



            auto newRes = std::make_shared<restaurant>(id, name, address , isActive , preparationTime , phonenumber1); 
            
            addRestaurant(newRes);
        }
        else if (choice == 3) {
            std::cout << "\033[2J\033[H";
            displayAllRestaurants();
            if (allRestaurants.empty()) {
                std::cout << "\nPress Enter to return...";
                std::cin.ignore();
                std::cin.get();
                continue;
            }
            std::string resName;
            std::cout << "Enter the name of the restaurant to remove: ";
            std::cin.ignore();
            std::getline(std::cin, resName);

            removeRestaurant(resName);

            std::cout << "\nPress Enter to return...";
            std::cin.get();
        }
        else if (choice == 4) {
            std::cout << "\nLogging out from Admin Panel...\n";
            break;
        }
    }
}



