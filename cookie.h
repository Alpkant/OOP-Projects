/***********************
Author:Alperen Kantarci
Number:150140140
***********************/

//Compile command as following
//g++ DessertShop.cpp icecream.cpp cookie.cpp candy.cpp 

#ifndef COOKIE_H
#define COOKIE_H
#include <cstring>
#include <iostream>
class Cookie{
    char* name;
    int number;
    int pricePerDozen;
public:
    Cookie();
    Cookie(const char*,const int,const int);
    Cookie(const Cookie&);      //Copy Constructor
    float getTotalPrice(const float)const;
    const Cookie& operator=(const Cookie&);
    friend std::ostream& operator<<(std::ostream& , const Cookie& );
    int getNumber()const;
    char* getName()const;
    int getPricePerDozen()const;
    float getTotalPrice()const;
    ~Cookie();
};
#endif
