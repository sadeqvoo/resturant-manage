#ifndef MENUITEM_H
#define MENUITEM_H

#include<string>

enum class ItemType 
{
    Food,
    Beverage,
};

class menuitem 
{
    protected:
    std::string ID ;
    std::string name ; 
    std::string description  ;
    double baseprice ;
    ItemType type ;
    bool isAvailable ;

    public:
    menuitem() = default;
    menuitem(std::string ID , std::string name , std::string description , double baseprice , ItemType type , bool isAvailable ) ;

    virtual ~menuitem() = default;

    std::string getID() const {return ID ;} 
    std::string getname() const {return name ;} 
    std::string getdescription() const {return description ;} 
    double getbaseprice() const {return baseprice ;} 
    ItemType getType() const {return type ;} 
    std::string getTypestring() const ;
    bool getisAvailable() const {return isAvailable ;} 


    void setname(const std::string & newname ) {name = newname ;} 
    void setdescription(const std::string & setdescripsion) {description = setdescripsion ;}
    void setbaseprice(double price) {baseprice = price ;}
    void setisAvailable (bool Available) {isAvailable = Available ;}

    virtual double calculateFinalPrice() const {return 0.0 ;};
};


#endif 