/***********************
Author:Alperen Kantarci
Number:150140140
***********************/

//Compile command as following
//g++ DessertShop.cpp icecream.cpp cookie.cpp candy.cpp 
#ifndef SHOP_H
#define SHOP_H
#include <iostream>
#include <cstring>

template <class Type>
class Shop{
    int number;
    Type* products;
    int  discountRate;
public:
    Shop();
    Shop(Type&);
    static int taxRate;
    void setDiscount(const int );
    void add(Type& );
    Type& operator[](const int);
    friend std::ostream& operator <<(std::ostream&, const Type&);
    Type& getProduct(int)const;
    int getNumber()const;
    int getDiscountRate()const;
    int getTaxRate()const;
    Type& findProduct(const char*);
    ~Shop();
};


template <class Type>
Shop<Type>::~Shop(){
    if(number!=0)
        delete [] products;
}

template <class Type>
Type& Shop<Type>::findProduct(const char* key){
    for (int i = 0; i < number; ++i)
    {
        if(strcmp(products[i].getName(),key) == 0)
            return products[i];    
    }
    throw "There is no matching product!";
}



template <class Type>
int Shop<Type>::taxRate=8;


template <class Type>
Type& Shop<Type>::getProduct(int key)const{
    return products[key];
}

template<class Type>        //Empty shop
Shop<Type>::Shop(){
    products =NULL;
    number=0;
    discountRate=0;
}

template <class Type>
Shop<Type>::Shop(Type& key){
    products = new Type[1];
    number=0;
    products[number] = key;
    discountRate=0;
    number++;
}



template <class Type>
void Shop<Type>::setDiscount(const int key){
    if(key<0 || key>30)
        throw "Discount rate is out of range!\n";
    discountRate=key;
}

template <class Type>
void Shop<Type>::add(Type& key){     
    Type* temp = new Type[number+1];
    int i;
    for (i = 0; i < number; ++i)
        temp[i] = products[i];
    
    temp[i]=key;
    if(products != NULL)
    delete [] products;
    products=temp;
    number++;
}

template<class Type>
Type& Shop<Type>::operator[](const int key){            //Subscript operator overload
    if(key>number-1)
      throw "We don't have enough cookies!\n" ;
    return products[key];       
}
 
template<class Type>
std::ostream& operator <<(std::ostream& os, const Shop<Type>& key)  
{
    float total=0;
    os << "***************\n" << "Number of items:" << key.getNumber() << "\n"; 
    for (int i = 0; i < key.getNumber(); ++i)
    {
         os << i+1 <<  ": " << key.getProduct(i) << "\n";
         total+=key.getProduct(i).getTotalPrice();
    }
    total += (total*key.getTaxRate()) / 100;
    os << "***************\nTotal cost: " << total <<"\n";
    if(key.getDiscountRate() != 0){
        os << "Discount: " << key.getDiscountRate() << "% \n";
        os << "Discount amount: -" << (total*key.getDiscountRate())/100 <<"\n";
        total-=(total*key.getDiscountRate())/100;
        os << "Discounted cost: " << total  << "\n";
    }
        os << "***************";

    return os;  
}  

template<class Type>
int Shop<Type>::getNumber()const{
    return number;
}

template<class Type>
int Shop<Type>::getDiscountRate()const{
    return discountRate;
}

template<class Type>
int Shop<Type>::getTaxRate()const{
    return taxRate;
}

#endif
