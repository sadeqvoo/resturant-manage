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
    cart orderItem ;
    double totalAmount ;

    int orderHour;

    public:
    order(int ID1 , OrderStatus status1,int restaurantID1 , cart orderItem1 , double totalAmount1) ;
    ~order() = default ;

    int getID() const {return ID ;}
    int getRestaurantID() const { return restaurantID; }
    OrderStatus getStatus() const {return status ;}
    std::string getStatusString() const ; 
    double gettotalAmount() const {return totalAmount ;}
     cart & getorderItem () {return orderItem ;} 
    const cart & getorderItem () const {return orderItem ;} 

    int getOrderHour() const { return orderHour; }
    void setOrderHour(int hour) { orderHour = hour; }


    void displayOrderDetails() const ;

    void setStatus(std::string newStatus);
};


#endif 