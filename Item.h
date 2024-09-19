/*Name: Jivin Chugh
Student id: 156056210
email: jchugh@myseneca.ca
date: 9 April 2023
-------------------------------------------------------------------------------------------------
For this part of milestone, all the work was done by myself, rest I took help from Amitoj in doing
some of the last parts.
-------------------------------------------------------------------------------------------------*/

#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include <fstream>
#include <iostream>
#include "Error.h"
#include "POS.h"
#include "PosIO.h"

namespace sdds
{
	class Item : public PosIO
	{
	private:

		//SKU
		//A C - string to keep an SKU code up to MAX_SKU_LEN characters.
		char m_sku[MAX_SKU_LEN + 1];
		
		//Name
		//A dynamically allocated C - string to keep the name of the Item up to MAX_NAME_LEN characters.
		char* m_itemname;
		
		//Price
		//A double value
		double m_price;
		
		//Taxed
		//A boolean that indicates if the Item is taxable or not.
		bool m_taxable;
		
		//Quantity
		//An integer value for the stock number of the Item. (number of items in the shop)
		int m_quantity;

	protected:
		//displayType
		//An integer flag that can be either POS_LIST to display the Item in List mode 
		//or POS_FORM to display the Item in Form mode.
		int m_displaytype;

		//Error State
		//An Error object to keep the error status of the Item.
		Error m_error;

	public:
		//Constructor
		//Item is instantiated using no arguments.In this case, 
		//an Item is set to an invalid Empty state(we will refer to this as empty from now on).
		Item();

		//Rule of three
		~Item();
		Item(const Item& obj);
		Item& operator=(const Item& obj);
		
		//operator==
		bool operator==(const char* sku)const;

		//operator>
		bool operator>(const Item& right)const;

		//opertor+=
		int operator+=(int quantity);
		int operator--();

		//operator-=
		int operator-=(int quantity);

		//bool type conversion
		operator bool()const;

		//helper += operator overload
		//Overload the operator+= to receive a double reference as the left - hand 
		//operand and a constant reference of Item as the right - hand operator. 
		//This operator should add the product of cost() by quantity() of the Item 
		//to the double operand and then return the value.
		//double& operator+=(double& cost, const Item& item);

		//Member function(Methods)
		//itemType
		//This pure virtual method returns a character as the type indicator 
		//of the item in future descendants of the Item.This method does not modify the object.
		virtual char itemType()const = 0;

		//displayType
		Item& displayType(int POStype);

		//cost query
		double cost()const;

		//quantity query
		int quantity()const;

		//clear
		Item& clear();

		//write
		std::ostream& write(std::ostream& os)const override;
		
		//save
		std::ofstream& save(std::ofstream& os)const override;
		
		//read
		std::istream& read(std::istream& is) override;
		
		//load
		std::ifstream& load(std::ifstream& is) override;

		//billprint
		std::ostream& bprint(std::ostream& os)const;

		///*static*/ const char returnsku();
		char* returnsku();
		
	};
	
	//helper += operator overload
	//Overload the operator+= to receive a double reference as the left - hand 
	//operand and a constant reference of Item as the right - hand operator. 
	//This operator should add the product of cost() by quantity() of the Item 
	//to the double operand and then return the value.
	double operator+=(double& cost, const Item& item);
}

#endif // !SDDS_ITEM_H
