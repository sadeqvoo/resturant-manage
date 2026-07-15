#include <iostream>
#include "customer.h"


customer::customer(int id1 ,std::string username1, int points1 ,std::shared_ptr<MembershipLevel> levelStrategy1 , cart myCart1 ,std::vector<order> orderHistory1 , std::string rolename1):
id(id1) ,username(username1),points(points1) ,levelStrategy(levelStrategy1) ,myCart(myCart1) ,orderHistory(orderHistory1), user(rolename1) {}

customer::customer(int id1, std::string rolename1, int points1, std::string levelStr)
    : id(id1), user(rolename1), points(points1) 
{
    username = rolename1 ;
    levelStrategy = createMembershipLevel(levelStr);
}


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

std::vector<std::string> customer::getBadges() const 
{
    std::vector<std::string> badges;

    
    if (orderHistory.size() >= 5) {
        badges.push_back("Frequent Buyer");
    }

    
    bool hasNightOrder = false;
    for (const auto& ord : orderHistory) {
        std::string dateStr = ord.getOrderDateStr(); 
        
        if (dateStr.length() >= 13) { 
            std::string hourStr = dateStr.substr(11, 2); 
            int hr = std::stoi(hourStr);
            
            if (hr >= 23 || hr < 4) {
                hasNightOrder = true;
                break;
            }
        }
    }

    if (hasNightOrder) {
        badges.push_back("Night Owl  (Night-time Order Placed)");
    }
    return badges;
}

void customer::displayProfile() const {
    std::cout << "\n--- Customer Profile ---" << std::endl;
    std::cout << "Name: " << getUsername() << std::endl;
    std::cout << "Level: " << levelStrategy->getLevelName() << std::endl;
    
    std::cout << "Current Points: " << points << std::endl;
    
    if (levelStrategy->getPointsRequiredForNext() > 0) {
        std::cout << "Points needed for upgrade: " << levelStrategy->getPointsRequiredForNext() << std::endl;
    } else {
        std::cout << "You are at the maximum level (VIP)!" << std::endl;
    }
    
    std::vector<std::string> badges = getBadges();
    std::cout << "Badges earned: ";
    if (badges.empty()) {
        std::cout << "No badges earned yet. Keep ordering! " << std::endl;
    } else {
        std::cout << std::endl;
        for (const auto& badge : badges) {
            std::cout << "   - " << badge << std::endl;
        }
    }

    std::cout << "------------------------\n" << std::endl;
}

void customer::checkLevelUpgrade() 
{
    std::string currentLvl = levelStrategy->getLevelName();
    std::string newLvl = currentLvl;

    if (this->points >= 700) {
        newLvl = "VIP";
    } else if (this->points >= 300) {
        newLvl = "Gold";
    } else if (this->points >= 100) {
        newLvl = "Silver";
    } else {
        newLvl = "Normal";
    }

    if (newLvl != currentLvl) {
        this->levelStrategy = createMembershipLevel(newLvl);
        std::cout << "\nCONGRATULATIONS! You have been upgraded to [" 
                  << newLvl << "] Level! \n" << std::endl;
    }
}

double customer::checkout(const cart& activeCart, double baseShippingFee , double couponDiscountPercent ) 
{
    double basePrice = activeCart.gettotalAmount(); 
    
    if (basePrice == 0) {
        std::cout << "Your cart is empty! Cannot proceed to checkout.\n" << std::endl;
        return 0.0;
    }

    double discount = levelStrategy->calculateDiscount(basePrice);

    double couponDiscount = 0.0;
    if (couponDiscountPercent > 0.0) 
    {
        couponDiscount = basePrice * (couponDiscountPercent / 100.0);
    }

    double shippingFee = levelStrategy->calculateShippingFee(baseShippingFee);
    double totalAmount = basePrice - discount - couponDiscount + shippingFee;
    int pointsEarned = levelStrategy->calculatePointsEarned(totalAmount);

    

    std::cout << "\n--- FINAL INVOICE ---" << std::endl;
    std::cout << "Base Price:          " << basePrice << " Toman" << std::endl;
    std::cout << "Level Discount (-):  " << discount << " Toman (" << levelStrategy->getLevelName() << ")" << std::endl;
    if (couponDiscount > 0.0) 
    {
        std::cout << "Coupon Discount (-): " << couponDiscount << " Toman (" << couponDiscountPercent << "% Off)" << std::endl;
    }
    std::cout << "Shipping Fee (+):    " << shippingFee << " Toman" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "TOTAL PAYABLE:       " << totalAmount << " Toman" << std::endl;
    std::cout << "Reward Points:       +" << pointsEarned << " points" << std::endl;
    std::cout << "---------------------\n" << std::endl;

    this->points += pointsEarned;

    this->checkLevelUpgrade();
    return totalAmount;
}

void customer::displaymeno() {
    std::cout << "Displaying Customer Menu..." << std::endl;
}