#include "cart.h"
#include <iostream>


cart::cart() {}

void cart::addtocart(std::string name , int a)
{
    for (size_t j = 0; j < cartin.size(); j++)
    {
        if (cartin[j].item != nullptr) 
        {
            if (cartin[j].item->getname() == name)
            {
                cartin[j].number = a ;
                return; 
            }
        }
    }
    cartitem newCartIn ;
    newCartIn.number = a ;
    
    newCartIn.item = nullptr;
    newCartIn.item->setname(name) ; 
    
    cartin.push_back(newCartIn) ;
}

void cart::removefromcart(std::string name , int a)
{
    for(size_t j = 0 ; j < cartin.size() ; j++)
    {
        if (cartin[j].item != nullptr && name == cartin[j].item->getname())
        {
            if(a < cartin[j].number) 
            {
                cartin[j].number = cartin[j].number - a ;
                return ;
            }
            else{
            cartin.erase(cartin.begin() + j) ;
            std::cout << "\n" << name << " removed from your cart.\n" ;
            return;
            }
        }
    }
    std::cout << "\nItem not found in your cart!" << std::endl;
}

void cart::clearcart() 
{
    cartin.clear();
}

double cart::gettotalAmount() const 
{
    double total = 0.0;

    for (size_t j = 0; j < cartin.size() ; j++) 
    {
        if(cartin[j].item != nullptr)
        {
            total += (cartin[j].item->getbaseprice() * cartin[j].number);
        }
    }
    return total;
}

std::vector<cartitem> cart::getorderItem() const 
{
    return cartin ;
}

void cart::displayCart() const 
{
    if (cartin.empty()) 
    {
        std::cout << "Your shopping cart is empty.\n" << std::endl;
        return;
    }

    for(size_t u = 0 ; u < cartin.size() ; u++)
    {
        if(cartin[u].item != nullptr)
        {
            std::cout << cartin[u].item->getname() << "-" << cartin[u].number << std::endl ;
        }
    }
}
