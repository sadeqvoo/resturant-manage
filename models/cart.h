#ifndef CART_H
#define CART_H

#include <string>
#include <vector>
#include <memory>    
#include "menuitem.h"

struct cartitem
{
    std::shared_ptr<menuitem> item;
    int number ;
};


class cart 
{
    private:
    std::vector<cartitem> cartin ;

    public:
    cart() ;
    ~cart() = default ;

    void addtocart(std::shared_ptr<menuitem> item, int a);
    void removefromcart (std::string name , int a) ;
    void clearcart() ;
    double gettotalAmount() const;
    void displayCart () const ;
    std::vector<cartitem> getorderItem() const ;

    
};


#endif