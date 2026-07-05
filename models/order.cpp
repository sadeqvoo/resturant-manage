#include "order.h"
#include <iostream>

order(int ID1 , OrderStatus status1 , std::vector<cartitem> orderItem1 , double totalAmount1) :
ID(ID1) , status(status1) , orderItem(orderItem1) , totalAmount(totalAmount1) {}

std::string order::getStatusString() const
{
    if (status = Preparing)
    {
        return "preparing" ;
    }
    else if(status = ReadyForShipping) 
    {
        return "ReadyForShipping" ;
    }
    else if (statuse = Delivered)
    {
        return "Delivered" ;
    } 
    else return "Unknown Status";

}

void order::setStatus(OrderStatus newStatus) { status = newStatus; }
