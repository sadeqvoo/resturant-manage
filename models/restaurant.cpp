

#include <iostream>
#include "restaurant.h"


void restaurant::addItemToMenu(std::shared_ptr<menuitem> item)
{
    menu.push_back(item) ;
}

void restaurant::removeItemFromMenu(std::string itemID)
{
    for (size_t i = 0 ; i < menu.size() ; i++ )
    {
        if (menu[i]->getID() == itemID)
        {
            menu.erase(menu.begin() + i);
            break ;
        }
    }
}

std::shared_ptr<menuitem> restaurant::finditemById (std::string itemID) const
{
    for (size_t i = 0; i < menu.size(); i++)
    {
        if (menu[i]->getID() == itemID)
        {
            return menu[i]; 
        }
    }
    return nullptr; 

}

void restaurant::displayMenu() const
{
    if (menu.empty()) 
    { 
        std::cout << "This restaurant's menu is currently empty!\n" ;
        return;
    }

    std::cout << "\n--------------------------------------------------\n" ;
    std::cout << " |ID " << getID() << " | Name "<< getname()<<" | address " << getaddress() << " | isActive " << getisActive() << " | preparationTime " << getpreparationTime() 
    <<" | phonenumber " << getphonenumber() << " | description " << getdescription() << std::endl ;
    std::cout << "--------------------------------------------------\n" ;


    std::cout << "--------------------MENU--------------------\n" ;
    for(size_t i = 0 ; i < menu.size() ; i++)
    {
        std::cout << i+1 << "-" ;
        std::cout << menu[i]->getname() << "\nID:" << menu[i]->getID() <<"\nItemType:" << menu[i]->getTypestring() << "\nbasePrice:" << menu[i]->getbaseprice() << "\ndescription:" << menu[i]->getdescription() ;
        if (menu[i]->getisAvailable() == true) std::cout << "\nexist:Yes" ;
        else std::cout << "\nexist:No" ;
        std::cout << "\n-------------------------------------------\n" ;
    }


}