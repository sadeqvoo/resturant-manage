#include "food.h"

food::food(std::string ID, std::string name, std::string description, double baseprice, bool isAvailable, int cookingTime)
    : menuitem(ID, name, description, baseprice, ItemType::Food, isAvailable), cookingTime(cookingTime)
{}

double food::calculateFinalPrice() const 
{
    return getbaseprice();
}