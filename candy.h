/***********************
Author:Alperen Kantarci
Number:150140140
***********************/

//Compile command as following
//g++ DessertShop.cpp icecream.cpp cookie.cpp candy.cpp 
#ifndef CANDY_H
#define CANDY_H
#include <cstring>
#include <iostream>
class Candy{
    char* name;
    float weight;
    int pricePerKilo;
public:
	Candy();
    Candy(const char*,const float,const int);
    Candy(const Candy&);                //Copy Constructor
    friend std::ostream& operator<<(std::ostream&,const Candy&);
    const Candy& operator=(const Candy&);
    float getWeight()const;
    int getPricePerKilo()const;
    char* getName()const;
    float getTotalPrice()const;
    float getTotalPrice(const float)const;
    ~Candy();
};

#endif
