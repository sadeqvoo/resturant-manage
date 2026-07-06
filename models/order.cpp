#include "order.h"
#include <iostream>

order::order(int ID1 , OrderStatus status1 , int restaurantID1 , cart orderItem1 , double totalAmount1) :
ID(ID1) , status(status1) ,restaurantID(restaurantID1), orderItem(orderItem1) , totalAmount(totalAmount1) {}

std::string order::getStatusString() const
{
    if (status == preparing)
    {
        return "preparing" ;
    }
    else if(status == ReadyForShipping) 
    {
        return "ReadyForShipping" ;
    }
    else if (status == Delivered)
    {
        return "Delivered" ;
    } 
    else return "Unknown Status";

}

void order::setStatus(OrderStatus newStatus) { status = newStatus; }
