#include "user.h"

user::user(std::string role) 
{
    rolename = role ;
}

std::string user::getrole() const 
{
    return rolename ;
}
