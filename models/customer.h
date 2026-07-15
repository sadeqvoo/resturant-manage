#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"
#include "cart.h"
#include <string>
#include <vector>
#include <memory>
#include "restaurant.h"
#include "order.h"
#include "MembershipLevel.h"


class customer : public user 
{
    private:
    cart myCart ;
    std::vector<order> orderHistory ;   

    int id; 
    std::string username ; 
    int points;
    std::shared_ptr<MembershipLevel> levelStrategy;

    public:
    customer(int id ,std::string username1, int points , std::shared_ptr<MembershipLevel> levelStrategy1 , cart myCart1 ,std::vector<order> orderHistory1 , std::string rolename1) ;
    customer(int id, std::string rolename, int points, std::string levelStr);

    ~customer() = default ;

    void displaymeno() override;
    
    void checkLevelUpgrade();
    
    int getPoints() const { return points; }
    std::shared_ptr<MembershipLevel> getMembershipLevel() const { return levelStrategy ; }
    int getID() const { return id; }
    std::string getUsername() const {return username ;}

    std::vector<std::string> getBadges() const;
    
    double checkout(const cart& activeCart, double baseShippingFee , double couponDiscountPercent = 0.0);
    void addOrderToHistory(const order& newOrder);
    void displayOrderHistory() const;
    void displayProfile() const;

};





#endif