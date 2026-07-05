#include "beverage.h"

beverage::beverage(std::string ID, std::string name, std::string description, double baseprice, bool isAvailable, int volume):
menuitem(ID , name , description , baseprice , ItemType::Beverage, isAvailable ), volume(volume) {}

double beverage::calculateFinalPrice() const 
{
    return getbaseprice();
}