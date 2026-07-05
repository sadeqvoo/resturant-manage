#ifndef BEVERAGE_H
#define BEVERAGE_H

#include "menuitem.h"

class beverage : public menuitem 
{
    private:
    int volume ;

    public:
    beverage(std::string ID, std::string name, std::string description, double baseprice, bool isAvailable, int volume);
    virtual ~beverage() = default ;

    int getVolume() const {return volume ;}
    void setVolume(int Volume) {this->volume = Volume ;}

    double calculateFinalPrice() const override;



};

#endif