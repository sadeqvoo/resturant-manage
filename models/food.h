#ifndef FOOD_H
#define FOOD_H

#include "menuitem.h"

class food : public menuitem
{
    private:
    int cookingTime ;

    public:
    food ( std::string ID , std::string name , std::string description , double baseprice  , bool isAvailable , int cookingTime ) ;
    virtual ~food () = default ;

    int getcookingTime() const {return cookingTime ;}
    void setcookingTime(int time) {cookingTime = time ; }

    double calculateFinalPrice() const override ;
};

#endif