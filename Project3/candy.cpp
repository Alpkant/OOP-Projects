/***********************
Author:Alperen Kantarci
Number:150140140
***********************/

//Compile command as following
//g++ DessertShop.cpp icecream.cpp cookie.cpp candy.cpp 

#include "candy.h"

Candy::Candy(){			//Empty candy
	name=NULL;
	weight=0;
	pricePerKilo=0;
}

Candy::Candy(const char* keyName,const float keyWeight,const int keyPrice){
    name= new char[strlen(keyName)];
    strcpy(name,keyName);
    weight=keyWeight;
    pricePerKilo=keyPrice;
}

Candy::Candy(const Candy& key){
    Candy(key.getName(),key.getWeight(),key.getPricePerKilo());
}

Candy::~Candy(){
	if(name!=NULL)
		delete [] name;
}

std::ostream& operator<<(std::ostream& os,const Candy& key){

	os << key.getName() << " #" << key.getWeight() << " Cost: "<< key.getTotalPrice()  << "\n"; 
	return os;
}

const Candy& Candy::operator=(const Candy& key){
    delete [] name;
    name=new char[strlen(key.getName())];
    strcpy(name,key.getName());
    weight=key.getWeight();
    pricePerKilo=key.getPricePerKilo();
    return *this;
}

float Candy::getWeight()const{
	return weight;
}

int Candy::getPricePerKilo()const{
	return pricePerKilo;
}

char* Candy::getName()const{
	return name;
}

float Candy::getTotalPrice()const{
	return weight*pricePerKilo;
}

float Candy::getTotalPrice(float key)const{
	return key*pricePerKilo;
}