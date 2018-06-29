/***********************
Author:Alperen Kantarci
Number:150140140
***********************/

//Compile command as following
//g++ DessertShop.cpp icecream.cpp cookie.cpp candy.cpp 

#include "cookie.h"

Cookie::Cookie(){       //Empty Cookie
    name=NULL;
    number=0;
    pricePerDozen=0;
}

Cookie::Cookie(const char* keyName,const int keyNumber,const int keyPrice){
    name= new char[strlen(keyName)];
    strcpy(name,keyName);
    number=keyNumber;
    pricePerDozen=keyPrice;
}


Cookie::Cookie(const Cookie& key){      
    Cookie(key.getName(),key.getNumber(),key.getPricePerDozen());
}

Cookie::~Cookie(){
    if(name!=NULL)
        delete [] name;
}

std::ostream& operator<<(std::ostream& os,const Cookie& key){
    os << key.getName() << " #" << key.getNumber() << " Cost: "<< key.getTotalPrice() << "\n"; 
    return os;
}

const Cookie& Cookie::operator=(const Cookie& key){
    delete [] name;
    name=new char[strlen(key.getName())];
    strcpy(name,key.getName());
    number=key.getNumber();
    pricePerDozen=key.getPricePerDozen();
    return *this;
}


int Cookie::getNumber()const{
    return number;
}


int Cookie::getPricePerDozen()const{
    return pricePerDozen;
}

char* Cookie::getName()const{
    return name;
}

float Cookie::getTotalPrice()const{
    return  number*pricePerDozen/12;
}

float Cookie::getTotalPrice(const float key)const{
    return   key*pricePerDozen/12;
}