#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
#include <vector>
#include <memory>
#include "menuitem.h"

class restaurant 
{
    private:
    int ID ;
    std::string name ;
    std::string address ;
    bool isActive ;
    int preparationTime ;
    std::string phonenumber ;
    std::string description ;

    std::vector<std::shared_ptr<menuitem>> menu;

    public:
    restaurant(int ID1 , std::string name1 , std::string adress1 , bool isActive1 , int preparationTime1 , std::string phonenumber1 , std::string description1) : 
    ID(ID1) , name(name1) , address(adress1) , isActive(isActive1) , preparationTime(preparationTime1) , phonenumber(phonenumber1) , description(description1) {}

    ~restaurant() = default ;

    void addItemToMenu(std::shared_ptr<menuitem> item) ;
    void removeItemFromMenu (std::string itemID) ;
    void displayMenu() const;
    std::shared_ptr<menuitem> finditemById(std::string itemID) const;


    int getID() const {return ID ;}
    std::string getname() const {return name ;}
    std::string getaddress() const {return address ;}
    bool getisActive() const {return isActive ;}
    int getpreparationTime() const {return preparationTime ;}
    std::string getphonenumber () const {return phonenumber ;}
    std::string getdescription () const {return description ;}
    const std::vector<std::shared_ptr<menuitem>>& getMenu() const { return menu; }

    void setname(std::string name2) {name = name2 ;}
    void setaddress(std::string address2) {address = address2 ;}
    void setisActive (bool isActive2) {isActive = isActive2 ;}
    void setpreparationTime(int preparationTime2 ) {preparationTime = preparationTime2 ;}
    void setphonenumber (std::string phonenumber2) {phonenumber = phonenumber2 ;}
    void setdescription (std::string description2) {description = description2 ;}



};

#endif