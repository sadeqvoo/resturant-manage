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
    public:
    customer(cart myCart1 ,std::vector<order> orderHistory1 , std::string rolename1) ;
    ~customer() = default ;

    void handleMenu(const std::vector<std::shared_ptr<restaurant>>& allRestaurants) ;
    
    void addOrderToHistory(const order& newOrder);
    
    void displayOrderHistory() const;
};





#endif