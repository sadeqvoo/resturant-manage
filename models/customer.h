#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"
#include "cart.h"
#include <string>
#include <vector>
#include <memory>
#include "restaurant.h"
#include "order.h"

class customer : public user 
{
    private:
    cart myCart ;
    std::vector<order> orderHistory ;   

    int id; 
    int points;
    std::string membership_level;

    public:
    customer(int id , int points , std::string membership_level , cart myCart1 ,std::vector<order> orderHistory1 , std::string rolename1) ;
    ~customer() = default ;

    int getPoints() const { return points; }
    std::string getMembershipLevel() const { return membership_level; }
    int getID() const { return id; }
    
    void addOrderToHistory(const order& newOrder);
    void displayOrderHistory() const;
    void displayProfile() const;
};





#endif