/***********************
Author:Alperen Kantarci
Number:150140140
***********************/

//Compile command as following
//g++ DessertShop.cpp icecream.cpp cookie.cpp candy.cpp 

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip> 
#include <fstream>
#include "shop.h"
#include "candy.h"
#include "cookie.h"
#include "icecream.h"

using namespace std;

int main() {
	fstream fs;
	fs.open("output.txt",fstream::out);

	Cookie cookie1("Chocolate Chip Cookies",10, 180); //(name, pieces, priceperdozen)
	Cookie cookie2("Cake Mix Cookies", 16, 210);

	Shop<Cookie> cookieShop(cookie1);
	cookieShop.add(cookie2);
    
	cout<< cookieShop <<endl; //Write to console
	fs<< cookieShop <<endl;	  //Write to output.txt
	//Catch an exception here while trying to access the element at(2)
	try{
    cout << cookieShop[2] << endl;
    fs << cookieShop[2] << endl;
	}catch(const char* error){
		cout << error ;
		fs << error;
	}
	Icecream icecream1("Chocolate ice cream",1.5, 170); //(name, litre, priceperlitre)
	Shop<Icecream> icecreamShop(icecream1);
	cout<<icecreamShop<<endl;
	fs << icecreamShop<< endl;

	//Catch an exception here while trying to set the discount to(50)
	try{
	icecreamShop.setDiscount(50);	
	}catch(const char* error){
		cout << error;
		fs << error;
	}

	Candy candy2("Gummi bears",12,89); //(name, weight, priceperkg)
	Candy candy3("Hanukkah gelt",8,110);

	Shop<Candy> candyShop(candy2);
	candyShop.add(candy3);

	try{
	candyShop.setDiscount(15);	
	}catch(const char* error){
		cout << error;
		fs << error;
	}
    cout<<candyShop<<endl;
    fs << candyShop << endl;
    fs.close();
    /*
    	Because of file operation and calculations is not any similar with actual templates 
    	following code makes only file calculations.
			*/
	FILE* text;
	char TempLine[200];
	
	try{
		text = fopen("stock.txt","r");
		if(text == NULL)
			throw "FILE COULDN'T OPEN\n"; 

	}catch(const char* error){
		cout << error;
		return 0;
	}

	Shop<Cookie> FileCookieShop;		//Creating 3 default shop
	Shop<Candy> FileCandyShop;
	Shop<Icecream> FileIcecreamShop;
	int totalProduct=0;					//Total product number will be held
	float totalPrice=0;					//Total price number will be held

	int i=0;
	char* tokenized;
	char tokenizedName[50],tokenizedType[5],tokenizedNumber[10],tokenizedPrice[10]; //Temporary strings
	float tmpFloat;
	int tmpPrice=0,tmpInt=0;
	
	while(fgets(TempLine,200,text) !=NULL ){	//Reading from stock.txt
		if(i!=0){
			 int j=0;
			 tokenized = strtok (TempLine,"\t");
			 while(tokenized != NULL){		   //Parsing a line.
			 	if(j==0)
			 		strcpy(tokenizedName,tokenized);	//Name of product
			 	else if(j==1)
			 		strcpy(tokenizedType,tokenized);	//Type of product
			 	else if(j==2)
			 		strcpy(tokenizedNumber,tokenized);	//Quantity of product
			 	else if(j==3)
			 		strcpy(tokenizedPrice,tokenized);	//Price of product
			 	j++;

			 	tokenized=strtok(NULL,"\t");
			 }
			 tmpPrice= stoi(tokenizedPrice);
			 tmpInt=stoi(tokenizedType);

			 	if(tmpInt==1){				//If type is cookie
			 			tmpInt=stoi(tokenizedNumber);
			 			Cookie tmpCookie(tokenizedName,tmpInt,tmpPrice);
			 		FileCookieShop.add(tmpCookie);
			 	}
			 	else if(tmpInt==2){			//If type is cookie
			 		tmpFloat = stof(tokenizedNumber);
			 		Candy tmpCandy(tokenizedName,tmpFloat,tmpPrice);
			 		FileCandyShop.add(tmpCandy);
			 	}
			 	else if(tmpInt==3){			//If type is cookie
			 		tmpFloat = stof(tokenizedNumber);
			 		Icecream tmpIce(tokenizedName,tmpFloat,tmpPrice);
			 		FileIcecreamShop.add(tmpIce);
			 	}
			i++;
		}else								//If it's stock's first line pass to second line
			i++;
	}

	fclose(text);

	try{
		text = fopen("order.txt","r");
		if(text == NULL)
			throw "FILE COULDN'T OPEN\n"; 

	}catch(const char* error){
		cout << error;
		return 0;
	}

	fs.open("checkout.txt",fstream::out);
	
	
	string stream;

	while(fgets(TempLine,200,text)!=NULL){	//Read order.txt
		int j=0;
		tokenized = strtok (TempLine,"\t");
		while(tokenized!=NULL){
		if(j==0)
			strcpy(tokenizedName,tokenized);
		else if(j==1)
			strcpy(tokenizedType,tokenized);
		else if (j==2)
			strcpy(tokenizedNumber,tokenized);

		tokenized=strtok(NULL,"\t");
		j++;
		}
		tmpInt=stoi(tokenizedType);
		Cookie keyCookie;			//Temp 3 default products
		Candy keyCandy;
		Icecream keyIcecream;
		FileCookieShop.setDiscount(10);
		if(tmpInt==1){				//COOKIE
			tmpFloat = stof(tokenizedNumber);
			try{
			keyCookie = FileCookieShop.findProduct(tokenizedName);  //Find corresponding product in shop.

			if(keyCookie.getNumber() < tmpFloat)				   	//If stock does not have enough product to sell
				fs << "!!! We don't have " << tmpFloat << " (" << tokenizedName << ")s." << endl;
			
				totalProduct++;
				stream += to_string(totalProduct);
				stream += ": ";
				stream += keyCookie.getName();
				stream = stream + " #";
				if(keyCookie.getNumber() < tmpFloat){
				  stream += to_string((int)keyCookie.getNumber());
				  tmpInt =  keyCookie.getTotalPrice() -1;
				  totalPrice += tmpInt;
				}
				else{
					stream += to_string((int)tmpFloat);
					tmpInt += keyCookie.getTotalPrice(tmpFloat)-1;
					totalPrice += tmpInt;
				} 
				stream = stream + " Cost: " + to_string(tmpInt) + "\n";	
				
			}catch(const char* error){
				cout << error << "\n" ;
			}
		}
	 	else if(tmpInt==2){					//Candy
			tmpFloat = stof(tokenizedNumber);
			try{
			keyCandy = FileCandyShop.findProduct(tokenizedName);	//Find corresponding product in shop.
			if(keyCandy.getWeight() < tmpFloat)						//If stock does not have enough product to sell
				fs << "!!! We don't have " << tmpFloat << " (" << tokenizedName << ")s." << endl;
			
				totalProduct++;
				stream += to_string(totalProduct);
				stream += ": ";
				stream += keyCandy.getName();
				stream = stream + " #";
				if(keyCandy.getWeight() < tmpFloat){
				  stream += to_string((int)keyCandy.getWeight());
				  tmpInt =  keyCandy.getTotalPrice();
				  totalPrice += tmpInt;
				}
				else{
					stream += to_string((int)tmpFloat);
					tmpInt += keyCandy.getTotalPrice(tmpFloat);
					totalPrice += tmpInt;
				} 
				stream = stream + " Cost: " + to_string(tmpInt) + "\n";	
				
			}catch(const char* error){
				cout << error << "\n" ;
			}
	 	}
	 	else if(tmpInt==3){						//Icecream
	 		tmpFloat = stof(tokenizedNumber);
	 		try{
			keyIcecream = FileIcecreamShop.findProduct(tokenizedName);	//Find corresponding product in shop.
			if(keyIcecream.getLitre() < tmpFloat)						//If stock does not have enough product to sell
				fs << "!!! We don't have " << tmpFloat << " (" << tokenizedName << ")s." << endl;
			
				totalProduct++;
				stream += to_string(totalProduct);
				stream += ": ";
				stream += keyIcecream.getName();
				stream = stream + " #";
				if(keyIcecream.getLitre() < tmpFloat){
				  stream += to_string((int)keyIcecream.getLitre());
				  tmpInt =  keyIcecream.getTotalPrice();
				  totalPrice += tmpInt;
				}
				else{
					stream += to_string((int)tmpFloat);
					tmpInt += keyIcecream.getTotalPrice(tmpFloat);
					totalPrice += tmpInt;
				} 
				stream = stream + " Cost: " + to_string(tmpInt) + "\n";	
			}catch(const char* error){
				cout << error << "\n" ;
			}
	 	}

	}
	fclose(text);
	


	fs <<  "-----------------------\n" <<"Number of items:" << totalProduct << endl;
	stream += "**********************\n";
	fs << stream;
	totalPrice += totalPrice * FileCookieShop.getTaxRate() /100 ;	 //Calculate taxed price
	fs << "Total cost: "  << setprecision(7) <<  totalPrice << endl;
	fs << "Discount: %" << FileCookieShop.getDiscountRate() << endl; 
	fs << "Discount amount: -" << setprecision(7) << totalPrice* ((float) FileCookieShop.getDiscountRate() /100) << endl;
	fs << "Discounted cost: " << setprecision(7) << totalPrice - (totalPrice* (float) FileCookieShop.getDiscountRate() /100) << endl;
	fs << "**********************\n";
	fs.close();

}
	

/*
You will also
1) Read dessert stock and customer order from "stock.txt" and "order.txt", respectively.
2) Write the total cost with 10% discount to "checkout.txt".
Expected output for checkout:

!!! We don't have 7 (Orange Jelly Candy)s.
!!! We don't have 11 (Chocolate ice cream)s.
-----------------------
Number of items:2
1: Chocolate Chip Cookies #2 Cost: 100

2: Cake Mix Cookies #10 Cost: 150

**********************
Total cost: 270.0
Discount: 10%
Discount amount: -27.0
Discounted cost: 243.0
**********************
*/

