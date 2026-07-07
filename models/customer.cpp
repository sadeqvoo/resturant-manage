#include <iostream>
#include "customer.h"


customer::customer(cart myCart1 ,std::vector<order> orderHistory1 , std::string rolename1):
myCart(myCart1) ,orderHistory(orderHistory1), user(rolename1) {}

void customer::addOrderToHistory(const order& newOrder) 
{
    orderHistory.push_back(newOrder);
}

void customer::displayOrderHistory() const 
{
    std::cout << "\n--- ORDER HISTORY ---" << std::endl;
    if (orderHistory.empty()) {
        std::cout << "You haven't placed any orders yet.\n" << std::endl;
        return;
    }
    
    for (size_t i = 0; i < orderHistory.size(); i++) {
        std::cout << "Order #" << orderHistory[i].getID() 
                  << " | Total: " << orderHistory[i].gettotalAmount() << " Toman"
                  << " | Status: " << orderHistory[i].getStatusString() << std::endl;
    }
    std::cout << "---------------------\n" << std::endl;
}

/*
void customer::handleMenu(const std::vector<std::shared_ptr<restaurant>>& allRestaurants)
{
    int customerChoice = 0 ; 

    while(true)
    {

        std::cout << "\033[2J\033[H";

        std::cout << "\n========= CUSTOMER MENU =========\n" ;
        std::cout << "Role: " << getrole() << std::endl ;
        std::cout << "1. View Active Restaurants & Order Food\n" ;
        std::cout << "2. View Current Cart (Live Total)\n" ;
        std::cout << "3. View Order History (Tarikhche)\n" ;
        std::cout << "4. Logout\n" ;
        std::cout << "Enter choice: ";
        std::cin >> customerChoice;

        if (std::cin.fail()) 
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number. Press Enter to continue...";
            std::cin.get(); 
            continue;
        }

        if (customerChoice == 4) // ino havaset bashe kamel nist
        {
            std::cout << "\nLogging out from customer role...\n" ;
            break ;
        }
        else if (customerChoice == 1 )
        {
            if (allRestaurants.empty()) 
            {
                std::cout << "\nNo active restaurants available in the system right now!\n" ;
                std::cout << "Press Enter to return...";
                std::cin.ignore();
                std::cin.get();
                continue;
            }
            std::cout << "\n--- Active Restaurants ---" << std::endl;
            for (size_t i = 0 ; i < allRestaurants.size(); i++) 
            {
                std::cout << i + 1 << ". " << allRestaurants[i]->getname() << "\naddress:" << allRestaurants[i]->getaddress() <<"\npreparationTime:" <<allRestaurants[i]->getpreparationTime()
                << std::endl ;
            }
            std::cout << "0. Back to Customer Menu" << std::endl;
            std::cout << "--------------------------" << std::endl;

            int resChoice = 0;
            std::cout << "Select a restaurant by number: ";
            std::cin >> resChoice;

            if (resChoice <= 0 || resChoice > static_cast<int>(allRestaurants.size())) 
            {
                continue; 
            }

            std::shared_ptr<restaurant> selectedRes = allRestaurants[resChoice - 1];

            while(true)
            {
                std::cout << "\n=================================\n" ;
                std::cout << "   Menu of: " << selectedRes->getname() << std::endl;
                std::cout << "=================================" << std::endl;

                selectedRes->displayMenu();

                std::cout << "\n>>> LIVE CART TOTAL: " << myCart.gettotalAmount() << " Toman <<<\n" ;
                std::cout << "---------------------------------\n" ;
                std::cout << "1. Add item to cart / Change quantity\n" ;
                std::cout << "2. Remove item from cart\n" ;
                std::cout << "3. Finalize Order & Checkout (Nahayi kardan)\n" ;
                std::cout << "4. Back to Restaurant List\n" ;
                std::cout << "---------------------------------\n" ;
                std::cout << "Select an option (1-4): ";

                int menuOp = 0;
                std::cin >> menuOp;

                if (menuOp == 4) break; 

                if (menuOp == 1) 
                {
                    std::string itemName;
                    int count = 0;
                    std::cout << "Enter Food/Beverage Name exactly: ";
                    std::cin.ignore(); 
                    std::getline(std::cin, itemName);
                    std::cout << "Enter Quantity (Tedad): ";
                    std::cin >> count;

                    if (count > 0) {
                        std::shared_ptr<menuitem> selectedItem = nullptr;
                        for (const auto& item : currentRestaurantMenu) 
                        { 
                            if (item->getname() == itemName) 
                            {
                                selectedItem = item;
                                break;
                            }
                        }
                    } else {
                        std::cout << "\nQuantity must be greater than 0!" << std::endl;
                    }
                }

                else if (menuOp == 2) 
                {
                    std::string itemName;
                    std::cout << "Enter Food/Beverage Name to remove: ";
                 
                    std::cout << "Enter number you want to remove: " ;   
                    int a ;
                    std::cin.ignore();
                    std::getline(std::cin, itemName);
                    
                    myCart.removefromcart(itemName , a) ; 
                    std::cout << "\nItem process completed." << std::endl;
                }

                else if (menuOp == 3)
                {
                    if (myCart.gettotalAmount() == 0) 
                    {
                        std::cout << "\nYour cart is empty! Cannot finalize order.\n" << std::endl;
                        continue;
                    }

                    std::cout << "\n--- Current Shopping Cart ---\n" ;
                    myCart.displayCart();

                    std::cout << "Confirm purchase and place order? (1: Yes / 0: No): ";
                    int confirm = 0;
                    std::cin >> confirm;

                    if (confirm == 1)
                    {
                        int resID = selectedRes->getID();
                        int generatedOrderID = 2000 + orderHistory.size();
                        order newOrder(generatedOrderID, OrderStatus::Preparing,resID, myCart , myCart.gettotalAmount());
                        std::cout << "\n======================================\n" ;
                        std::cout << "   ORDER REGISTERED SUCCESSFULY!      \n" ;
                        std::cout << "   Your Order ID: " << newOrder.getID() << std::endl ;
                        std::cout << "   Current Status: " << newOrder.getStatusString() << std::endl;
                        std::cout << "   Approximate Time: " << selectedRes->getpreparationTime() << std::endl; 
                        std::cout << "======================================\n" << std::endl ;

                        addOrderToHistory(newOrder);
                        myCart.clearcart();
                        std::cout << "Press Enter to continue...";
                        std::cin.ignore();
                        std::cin.get();
                        break; 
                        } 
                        else 
                        {
                            std::cout << "\nCheckout cancelled.\n" << std::endl;
                        }

                }
                
            }
        }
        else if (customerChoice == 2)
        {
            std::cout << "\033[2J\033[H";
            std::cout << "\n========= CURRENT SHOPPING CART =========" << std::endl;
            myCart.displayCart();
            std::cout << "Press Enter to return to Customer Menu...";
            std::cin.ignore();
            std::cin.get();
        }

        else if (customerChoice == 3)
        {
            std::cout << "\033[2J\033[H";
            displayOrderHistory();
            std::cout << "Press Enter to return to Customer Menu...";
            std::cin.ignore();
            std::cin.get();
        }

        
    }
}

*/