#include "order.h"
#include <iostream>

order::order(int ID1 , OrderStatus status1 , int restaurantID1 , cart orderItem1 , double totalAmount1) :
ID(ID1) , status(status1) ,restaurantID(restaurantID1), orderItem(orderItem1) , totalAmount(totalAmount1) {}

std::string order::getStatusString() const
{
    if (status == OrderStatus::Preparing)
    {
        return "preparing" ;
    }
    else if(status == OrderStatus::ReadyForShipping) 
    {
        return "ReadyForShipping" ;
    }
    else if (status == OrderStatus::Delivered)
    {
        return "Delivered" ;
    } 
    else return "Unknown Status";

}

void order::setStatus(std::string newStatus) 
{ 
    if (newStatus == "Preparing") status = OrderStatus::Preparing ;
    if (newStatus == "ReadyForShipping") status = OrderStatus::ReadyForShipping ;
    if (newStatus == "Delivered") status = OrderStatus::Delivered ;

}

void order::displayOrderDetails() const 
{
    std::cout << "Order ID: " << ID 
              << " | Restaurant ID: " << restaurantID 
              << " | Total: $" << totalAmount << std::endl;
    std::cout << "Items Ordered:" << std::endl;
    orderItem.displayCart(); 
}
