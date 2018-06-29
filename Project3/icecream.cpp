/***********************
Author:Alperen Kantarci
Number:150140140
***********************/

//Compile command as following
//g++ DessertShop.cpp icecream.cpp cookie.cpp candy.cpp 

#include "icecream.h"


Icecream::Icecream(){ //Empty Icecream
	name=NULL;
	litre=0;
	pricePerLitre=0;

}

Icecream::Icecream(const char* keyName, const float keyLitre, const int keyPrice){
    name= new char[strlen(keyName)];
    strcpy(name,keyName);
    litre=keyLitre;
    pricePerLitre=keyPrice;
}

Icecream::Icecream(const Icecream& key){
    Icecream(key.getName(),key.getLitre(),key.getPricePerLitre());
}

Icecream::~Icecream(){
    if(name!=NULL)
        delete [] name;
}



std::ostream& operator<<(std::ostream& os,const Icecream& key){

	os << key.getName() << " #" << key.getLitre() << " Cost: "<< key.getTotalPrice()  << "\n"; 
	return os;
}

const Icecream& Icecream::operator=(const Icecream& key){
    delete [] name;
    name=new char[strlen(key.getName())];
    strcpy(name,key.getName());
    litre=key.getLitre();
    pricePerLitre=key.getPricePerLitre();
    return *this;
}

float Icecream::getLitre()const{
	return litre;
}

int Icecream::getPricePerLitre()const{
	return pricePerLitre;
}

char* Icecream::getName()const{
	return name;
}

float Icecream::getTotalPrice()const{
	return 	litre*pricePerLitre;
}

float Icecream::getTotalPrice(const float key)const{
    return  key*pricePerLitre;
}

