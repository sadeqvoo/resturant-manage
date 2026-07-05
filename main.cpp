#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "sqlite3.h"

#include "database/RestaurantDAO.h"
#include "database/MenuDAO.h"
#include "database/OrderDAO.h"

using namespace std;

int main() {
    sqlite3* db = nullptr;
    int exit = sqlite3_open("restaurant_system.db", &db);

    if (exit != SQLITE_OK) {
        cerr << "Error opening database!" << endl;
        return -1;
    }
    cout << "--- Database connection established successfully ---" << endl;

    RestaurantDAO restaurantDAO(db);
    MenuDAO menuDAO(db);
    OrderDAO orderDAO(db);

    int mainChoice = 0;


    while (true) {
        cout << "\n=========================================" << endl;
        cout << "    Welcome to Restaurant System    " << endl;
        cout << "=========================================" << endl;
        cout << "1. Login as Admin" << endl;
        cout << "2. Login as Restaurant Manager" << endl;
        cout << "3. Login as Customer" << endl;
        cout << "4. Exit" << endl;
        cout << "Please enter your choice (1-4): ";
        cin >> mainChoice;

        if (mainChoice == 4) {
            cout << "\nThank you for using the system. Exiting..." << endl;
            break;
        }

        switch (mainChoice) {
            case 1: 
            {
                
                int adminChoice = 0;
                while (true) {
                    cout << "\n-----------------------------------------" << endl;
                    cout << "          System Admin Dashboard         " << endl;
                    cout << "-----------------------------------------" << endl;
                    cout << "1. View All Restaurants (Full Details)" << endl;
                    cout << "2. Register New Restaurant" << endl;
                    cout << "3. Activate / Deactivate a Restaurant" << endl;
                    cout << "4. View System Reports & Analytics" << endl;
                    cout << "5. Delete a Restaurant" << endl;
                    cout << "6. Back to Main Menu" << endl;
                    cout << "Enter your choice (1-6): ";
                    cin >> adminChoice;

                    if (adminChoice == 6) {
                        cout << "\nReturning to Main Menu..." << endl;
                        break;
                    }

                    switch (adminChoice) {
                        case 1: {
                            cout << "\n=== List of Restaurants ===" << endl;
                            std::vector<std::shared_ptr<restaurant>> resList = restaurantDAO.getAllRestaurants();
                            
                            if (resList.empty()) {
                                cout << "No restaurants registered yet." << endl;
                            } else {
                                for (const auto& res : resList) {
                                    std::string statusStr = res->getisActive() ? "Active" : "Inactive";
                                    cout << "ID: " << res->getID() 
                                         << " | Name: " << res->getname() 
                                         << " | Phone: " << res->getPhonenumber()
                                         << " | Prep Time: " << res->getPreparationTime() << " mins"
                                         << " | Address: " << res->getAddress()
                                         << " | Status: [" << statusStr << "]" << endl;
                                }
                            }
                            break;
                        }

                        case 2: 
                        {
                            int id, prepTime;
                            std::string name, address, phone;

                            cout << "\nEnter New Restaurant ID: ";
                            cin >> id;
                            cin.ignore(); 

                            cout << "Enter Restaurant Name: ";
                            std::getline(cin, name);

                            cout << "Enter Restaurant Address: ";
                            std::getline(cin, address);

                            cout << "Enter Preparation Time (in minutes): ";
                            cin >> prepTime;
                            cin.ignore();

                            cout << "Enter Phone Number: ";
                            std::getline(cin, phone);

                           
                            auto newRestaurant = std::make_shared<restaurant>(id, name, address, true, prepTime, phone , "");

                            if (restaurantDAO.insertRestaurant(newRestaurant)) {
                                cout << "SUCCESS: Restaurant registered successfully!" << endl;
                            } else {
                                cout << "ERROR: Failed to register restaurant." << endl;
                            }
                            break;
                        }

                        case 3: {
                            int resId, newStatus;
                            cout << "\nEnter Restaurant ID to toggle status: ";
                            cin >> resId;
                            cout << "Enter New Status (1 for Activate, 0 for Deactivate): ";
                            cin >> newStatus;

                            if (restaurantDAO.updateRestaurantStatus(resId, newStatus)) {
                                cout << "SUCCESS: Restaurant status updated successfully!" << endl;
                            } else {
                                cout << "ERROR: Failed to update status. Check Restaurant ID." << endl;
                            }
                            break;
                        }

                        case 4: {
                            cout << "\n=========================================" << endl;
                            cout << "        System Reports & Analytics       " << endl;
                            cout << "=========================================" << endl;
                            
                            std::vector<std::shared_ptr<order>> allOrders = orderDAO.getAllOrdersForCustomer();
                            double totalSales = 0.0;
                            int totalOrdersCount = allOrders.size();

                            for (const auto& ord : allOrders) {
                                totalSales += ord->getTotalPrice();
                            }

                            cout << ">> Total Registered Orders: " << totalOrdersCount << endl;
                            cout << ">> Total System Revenue   : $" << totalSales << endl;
                            cout << ">> Active Users Monitor   : 1 (Single Customer Session)" << endl;
                            cout << "-----------------------------------------" << endl;
                            break;
                        }

                        case 5: {
                            int resId;
                            cout << "\nEnter Restaurant ID to delete: ";
                            cin >> resId;

                            if (restaurantDAO.deleteRestaurant(resId)) {
                                cout << "SUCCESS: Restaurant deleted successfully!" << endl;
                            } else {
                                cout << "ERROR: Failed to delete restaurant." << endl;
                            }
                            break;
                        }

                        default:
                            cout << "\n Invalid choice! Please enter a number between 1 and 6." << endl;
                            break;
                    }
                }
                break;
            

            }
            case 2:
            {
                int targetResId;
                cout << "\n=========================================" << endl;
                cout << "         Restaurant Manager Login        " << endl;
                cout << "=========================================" << endl;
                cout << "Enter your Restaurant ID to manage: ";
                cin >> targetResId;

                int managerChoice = 0;
                while (true) {
                    cout << "\n-----------------------------------------" << endl;
                    cout << "    Manager Dashboard (Restaurant " << targetResId << ")    " << endl;
                    cout << "-----------------------------------------" << endl;
                    cout << "1. Manage Menu Items (Food/Drinks)" << endl;
                    cout << "2. Manage Active Orders" << endl;
                    cout << "3. Back to Main Menu" << endl;
                    cout << "Enter your choice (1-3): ";
                    cin >> managerChoice;

                    if (managerChoice == 3) {
                        cout << "\nExiting Manager Panel..." << endl;
                        break;
                    }

                                        
                    
                    if (managerChoice == 1) {
                        int menuChoice = 0;
                        while (true) {
                            cout << "\n--- Menu Items Management ---" << endl;
                            cout << "1. View Current Menu" << endl;
                            cout << "2. Add New Item to Menu" << endl;
                            cout << "3. Edit Existing Item" << endl;
                            cout << "4. Delete Item from Menu" << endl;
                            cout << "5. Back to Dashboard" << endl;
                            cout << "Enter choice (1-5): ";
                            cin >> menuChoice;

                            if (menuChoice == 5) break;

                            switch (menuChoice) {
                                case 1: {
                                    cout << "\n=== Current Menu ===" << endl;
                                    std::vector<std::shared_ptr<menuitem>> menuList = menuDAO.getMenuForRestaurant(targetResId);
                                    
                                    if (menuList.empty()) {
                                        cout << "Menu is empty." << endl;
                                    } else {
                                        for (const auto& item : menuList) {
                                            std::string availability = item->getisAvailable() ? "Available" : "Out of Stock";
                                            std::string typeStr = (item->getType() == ItemType::Food) ? "Food" : "Beverage";
                                            
                                            // Using your exact lowercase getters
                                            cout << "ID: " << item->getID() 
                                                 << " | Name: " << item->getname() 
                                                 << " | Type: " << typeStr
                                                 << " | Base Price: $" << item->getbaseprice()
                                                 << " | Status: [" << availability << "]" 
                                                 << "\n   Description: " << item->getdescription() << endl;
                                        }
                                    }
                                    break;
                                }

                                case 2: {
                                    std::string itemId, itemName, description;
                                    double basePrice;
                                    int typeChoice;
                                    ItemType itemType;

                                    cout << "\nSelect Item Type:" << endl;
                                    cout << "1. Food" << endl;
                                    cout << "2. Beverage" << endl;
                                    cout << "Enter choice (1-2): ";
                                    cin >> typeChoice;
                                    itemType = (typeChoice == 2) ? ItemType::Beverage : ItemType::Food;
                                    cin.ignore();

                                    cout << "Enter New Item ID (String/Code): ";
                                    std::getline(cin, itemId);

                                    cout << "Enter Item Name: ";
                                    std::getline(cin, itemName);

                                    cout << "Enter Base Price: ";
                                    cin >> basePrice;
                                    cin.ignore();

                                    cout << "Enter Item Description: ";
                                    std::getline(cin, description);

                                    
                                    std::shared_ptr<menuitem> newItem = nullptr;
                                    if (itemType == ItemType::Food) {
                                        newItem = std::make_shared<Food>(itemId, itemName, description, basePrice, itemType, true);
                                    } else {
                                        newItem = std::make_shared<Beverage>(itemId, itemName, description, basePrice, itemType, true);
                                    }

                                    if (menuDAO.insertMenuItem(targetResId, newItem)) {
                                        cout << "SUCCESS: Item added to menu!" << endl;
                                    } else {
                                        cout << "ERROR: Failed to add item." << endl;
                                    }
                                    break;
                                }

                                case 3: {
                                    std::string itemId, newDesc;
                                    double newPrice;
                                    int isAvailableInt;

                                    cin.ignore();
                                    cout << "\nEnter Item ID to edit: ";
                                    std::getline(cin, itemId);
                                    
                                    cout << "Enter New Base Price: ";
                                    cin >> newPrice;
                                    cin.ignore();
                                    
                                    cout << "Enter New Description: ";
                                    std::getline(cin, newDesc);
                                    
                                    cout << "Is Available? (1 for Yes, 0 for No): ";
                                    cin >> isAvailableInt;

                                    if (menuDAO.updateMenuItem(itemId, newPrice, newDesc, isAvailableInt == 1)) {
                                        cout << "SUCCESS: Menu item updated successfully!" << endl;
                                    } else {
                                        cout << "ERROR: Failed to update item. Verify ID." << endl;
                                    }
                                    break;
                                }

                                case 4: {
                                    std::string itemId;
                                    cin.ignore();
                                    cout << "\nEnter Item ID to delete from menu: ";
                                    std::getline(cin, itemId);

                                    if (menuDAO.deleteMenuItem(itemId)) {
                                        cout << "SUCCESS: Item deleted from menu!" << endl;
                                    } else {
                                        cout << "ERROR: Failed to delete item." << endl;
                                    }
                                    break;
                                }

                                default:
                                    cout << "\n Invalid option!" << endl;
                                    break;
                            }
                        }
                    }
                    // -----------------------------------------------------
                    // زیرمنو ۲: مدیریت سفارشات جاری رستوران
                    // -----------------------------------------------------
                    else if (managerChoice == 2) {
                        int orderChoice = 0;
                        while (true) 
                        {
                            cout << "\n--- Orders Management ---" << endl;
                            cout << "1. View Active Orders" << endl;
                            cout << "2. Update Order Status (Processing Stages)" << endl;
                            cout << "3. Back to Dashboard" << endl;
                            cout << "Enter choice (1-3): ";
                            cin >> orderChoice;

                            if (orderChoice == 3) break;

                            switch (orderChoice) {
                                case 1: {
                                    cout << "\n=== Active Orders for Your Restaurant ===" << endl;
                                    std::vector<std::shared_ptr<order>> orders = orderDAO.getOrdersForRestaurant(targetResId);

                                    if (orders.empty()) {
                                        cout << "No orders found for this restaurant." << endl;
                                    } else {
                                        for (const auto& ord : orders) {
                                            std::string statusText = "Pending";
                                            if (ord->getStatus() == 1) statusText = "Preparing";
                                            else if (ord->getStatus() == 2) statusText = "Ready For Shipping";
                                            else if (ord->getStatus() == 3) statusText = "Delivered";

                                            cout << "-----------------------------------------" << endl;
                                            cout << "Order ID: " << ord->getOrderID() 
                                                 << " | Total Price: $" << ord->getTotalPrice()
                                                 << " | Current Status: [" << statusText << "]" << endl;
                                            cout << "Items ordered:" << endl;
                                            
                                            for (const auto& item : ord->getCartItems()) {
                                                cout << "   - " << item.getname() << " x " << item.getQuantity() << endl;
                                            }
                                        }
                                    }
                                    break;
                                }

                                case 2: 
                                {
                                    int orderId, stageChoice;
                                    cout << "\nEnter Order ID to update: ";
                                    cin >> orderId;

                                    cout << "Select New Status Stage:\n";
                                    cout << "1. Preparing\n";
                                    cout << "2. Ready For Shipping\n";
                                    cout << "3. Delivered\n";
                                    cout << "Enter status number (1-3): ";
                                    cin >> stageChoice;

                                    OrderStatus newStatus;
                                    bool valid = true;
                                    if (stageChoice == 1) newStatus = OrderStatus::Preparing;
                                    else if (stageChoice == 2) newStatus = OrderStatus::ReadyForShipping;
                                    else if (stageChoice == 3) newStatus = OrderStatus::Delivered;
                                    else {
                                    cout << " Invalid status stage!" << endl;
                                    valid = false;
                                    }

                                    if (valid) {
                                    if (orderDAO.updateOrderStatus(orderId, static_cast<int>(newStatus))) {
                                     cout << "SUCCESS: Order status updated successfully!" << endl;
                                    } else {
                                        cout << "ERROR: Failed to update status." << endl;
                                        }
                                         }
                                        break;
                                    }

                                default:
                                    cout << "\n Invalid option!" << endl;
                                    break;
                            }
                        }
                    }
                    else {
                        cout << "\n Invalid choice! Please enter a number between 1 and 3." << endl;
                    }
                }
                break;
            }
            case 3: {
                int customerChoice = 0;

                while (true) {
                    cout << "\n-----------------------------------------" << endl;
                    cout << "              Customer Panel             " << endl;
                    cout << "-----------------------------------------" << endl;
                    cout << "1. Browse Restaurants & Start Ordering" << endl;
                    cout << "2. View My Order History & Status" << endl;
                    cout << "3. Back to Main Menu" << endl;
                    cout << "Enter your choice (1-3): ";
                    cin >> customerChoice;

                    if (customerChoice == 3) {
                        cout << "\nReturning to Main Menu..." << endl;
                        break;
                    }

                    
                    if (customerChoice == 1) {
                        cout << "\n=== Active Restaurants ===" << endl;
                        auto resList = restaurantDAO.getAllRestaurants();
                        int activeCount = 0;
                        
                        for (const auto& res : resList) {
                            if (res->getisActive()) {
                                cout << "ID: " << res->getID() 
                                     << " | Name: " << res->getname() 
                                     << " | Address: " << res->getAddress() 
                                     << " | Est. Prep Time: " << res->getPreparationTime() << " mins" << endl;
                                activeCount++;
                            }
                        }

                        if (activeCount == 0) {
                            cout << "No active restaurants available right now." << endl;
                            continue;
                        }

                        int selectedRestaurantId = -1;
                        cout << "\nEnter Restaurant ID to enter its menu (or 0 to cancel): ";
                        cin >> selectedRestaurantId;

                        if (selectedRestaurantId == 0) continue;

                        auto menuList = menuDAO.getMenuForRestaurant(selectedRestaurantId);
                        if (menuList.empty()) {
                            cout << " This restaurant has no items available or ID is invalid." << endl;
                            continue;
                        }

                        cart userCart; 
                        int resMenuChoice = 0;

                        while (true) {
                            cout << "\n=========================================" << endl;
                            cout << "   Ordering from Restaurant " << selectedRestaurantId << endl;
                            cout << "   [ LIVE CART TOTAL: $" << userCart.gettotalAmount() << " ]" << endl; 
                            cout << "=========================================" << endl;
                            cout << "1. View Restaurant Menu " << endl;
                            cout << "2. Add Item to Cart " << endl;
                            cout << "3. View Detailed Cart Items " << endl;
                            cout << "4. Change Quantity / Remove Item " << endl;
                            cout << "5. Finalize Order & Checkout " << endl;
                            cout << "6. Exit Restaurant & Clear Cart " << endl;
                            cout << "Enter choice (1-6): ";
                            cin >> resMenuChoice;

                            if (resMenuChoice == 6) {
                                cout << "Leaving restaurant. Cart cleared." << endl;
                                break; 
                            }

                            switch (resMenuChoice) {
                                case 1: { 
                                    cout << "\n--- Menu for Restaurant " << selectedRestaurantId << " ---" << endl;
                                    for (const auto& item : menuList) {
                                        if (item->getisAvailable()) {
                                            cout << "Name: " << item->getname() 
                                                 << " | Price: $" << item->getbaseprice() 
                                                 << " | Status: [Available]"
                                                 << "\n   Description: " << item->getdescription() << endl;
                                        }
                                    }
                                    break;
                                }

                                case 2: { 
                                    std::string targetItemName;
                                    int quantity;
                                    cin.ignore();
                                    cout << "\nEnter exact Item Name to add to cart: ";
                                    std::getline(cin, targetItemName);

                                    if (targetItemName.empty()) break;

                                    cout << "Enter Quantity: ";
                                    cin >> quantity;

                                    userCart.addtocart(targetItemName, quantity);
                                    cout << "SUCCESS: Cart updated!" << endl;
                                    break;
                                }

                                case 3: { 
                                    cout << "\n=== Current Cart Items ===" << endl;
                                    userCart.displayCart(); 
                                    break;
                                }

                                case 4: { 
                                    std::string itemName;
                                    int qtyToRemove;
                                    cin.ignore();
                                    cout << "\nEnter the exact Item Name to modify/remove: ";
                                    std::getline(cin, itemName);
                                    
                                    cout << "Enter quantity to reduce/remove: ";
                                    cin >> qtyToRemove;

                                    userCart.removefromcart(itemName, qtyToRemove);
                                    cout << "Cart updated successfully." << endl;
                                    break;
                                }

                                case 5: { 
                                    auto currentItems = userCart.getorderItem();
                                    if (currentItems.empty()) {
                                        cout << " Cannot checkout an empty cart! Please add items first." << endl;
                                        break;
                                    }

                                    char checkoutChoice;
                                    cout << "Are you sure you want to place this order for $" << userCart.gettotalAmount() << "? (y/n): ";
                                    cin >> checkoutChoice;

                                    if (checkoutChoice == 'y' || checkoutChoice == 'Y') {
                                        int newOrderId = rand() % 90000 + 10000; 

                                        auto newOrder = std::make_shared<order>(
                                            newOrderId, 
                                            OrderStatus::Preparing, 
                                            userCart.getorderItem(), 
                                            userCart.gettotalAmount()
                                        );

                                        if (orderDAO.insertOrder(newOrder)) {
                                            cout << "\n SUCCESS: Order placed successfully!" << endl;
                                            cout << ">> YOUR ORDER ID: #" << newOrderId << endl;
                                            cout << ">> CURRENT STATUS: Preparing" << endl;
                                            userCart.clearcart(); 
                                            resMenuChoice = 6; 
                                        } else {
                                            cout << " ERROR: Failed to save order." << endl;
                                        }
                                    }
                                    break;
                                }

                                default:
                                    cout << "\n Invalid choice!" << endl;
                                    break;
                            }

                            if (resMenuChoice == 6) break; 
                        }
                    }

                    else if (customerChoice == 2) {
                        cout << "\n=== Your Order History ===" << endl;
                        std::vector<std::shared_ptr<order>> history = orderDAO.getAllOrdersForCustomer();

                        if (history.empty()) {
                            cout << "You have no past orders." << endl;
                        } else {
                            for (const auto& ord : history) {
                                cout << "\n-----------------------------------------";
                                ord->displayOrderDetails(); 
                                cout << "Current Order Status: [" << ord->getStatusString() << "]" << endl; 
                                cout << "-----------------------------------------";
                            }
                            cout << endl;
                        }
                    }
                }
                break;
            }

            default:
                cout << "\n Invalid choice! Please enter a number between 1 and 4." << endl;
                break;
        }
    }

    sqlite3_close(db);
    return 0;
}