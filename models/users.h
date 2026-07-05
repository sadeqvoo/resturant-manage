#ifndef USER_H
#define USER_H


#include <string>

class user 
{
    protected:
    std::string rolename ;

    public:
    user (std::string rolename ) ;

    virtual ~user = default ;
    std::string getrole() const ;

    virtual void displaymeno () = 0 const ;
};





#endif