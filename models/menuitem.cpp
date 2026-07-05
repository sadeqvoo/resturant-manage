#include "menuitem.h"

menuitem::menuitem(std::string ID, std::string name, std::string description, double baseprice, ItemType type, bool isAvailable)
    : ID(ID), name(name), description(description), baseprice(baseprice), type(type), isAvailable(isAvailable) 
{
}