#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include "cart.h"

enum class OrderStatus
{
    Preparing,
    ReadyForShipping,
    Delivered
};

class order 
{
    private:
    int ID ;
    OrderStatus status;
    int restaurantID; 
    std::vector<cartitem> orderItem ;
    double totalAmount ;

    public:
    order(int ID1 , OrderStatus status1 , std::vector<cartitem> orderItem1 , double totalAmount1) ;
    ~order() = default ;

    int getID() const {return ID ;}
    OrderStatus getStatus() const {return status ;}
    std::string getStatusString() const ; 
    double gettotalAmount() const {return totalAmount ;}
    const std::vector<cartitem> & getorderItem () const {return orderItem ;} 
    
    void displayOrderDetails() const ;

    void setStatus(OrderStatus newStatus);
};


#endif 