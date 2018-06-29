/***********************
Author:Alperen Kantarci
Number:150140140
***********************/

//Compile command as following
//g++ DessertShop.cpp icecream.cpp cookie.cpp candy.cpp 
#ifndef ICECREAM_H
#define ICECREAM_H
#include <cstring>
#include <iostream>

class Icecream{
    char* name;
    float litre;
    int pricePerLitre;
public:
	Icecream();
    Icecream(const char*,const float,const int);
    Icecream(const Icecream&);              //Copy constructors 
    friend std::ostream& operator<<(std::ostream& ,const Icecream&);
    const Icecream& operator=(const Icecream&);
    float getLitre()const;
    int getPricePerLitre()const;
    char* getName()const;
    float getTotalPrice()const;
    float getTotalPrice(const float)const;
    ~Icecream();
};
#endif
