/*Name: Jivin Chugh
Student id: 156056210
email: jchugh@myseneca.ca
date: 9 April 2023
-------------------------------------------------------------------------------------------------
For this part of milestone, all the work was done by myself, rest I took help from Amitoj in doing 
some of the last parts.
-------------------------------------------------------------------------------------------------*/


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cstring>
#include "Item.h"
#include "Error.h"

using namespace std;

namespace sdds
{
	Item::Item()
	{
		this->m_sku[0] = '\0';
		this->m_itemname = nullptr;
		this->m_price = 0.0;
		this->m_taxable = true;
		this->m_quantity = 0;
		this->m_displaytype = 0;
	}

	Item::~Item()
	{
		delete[] m_itemname;
	}

	Item::Item(const Item& obj)
	{
		*this = obj;
	}

	Item& Item::operator=(const Item& obj)
	{
		if (this != &obj) 
		{
			strcpy(this->m_sku, obj.m_sku);
			if (this->m_itemname != nullptr) 
			{
				delete[] this->m_itemname;
				this->m_itemname = nullptr;
			}
			if (obj.m_itemname != nullptr)
			{
				this->m_itemname = new char[strlen(obj.m_itemname) + 1];
				strcpy(this->m_itemname, obj.m_itemname);
			}
			this->m_price = obj.m_price;
			this->m_taxable = obj.m_taxable;
			this->m_quantity = obj.m_quantity;
			this->m_displaytype = obj.m_displaytype;
			this->m_error = obj.m_error;
		}
		return *this;
	}

	bool Item::operator==(const char* sku) const
	{
		//Compares an Item to a C - string and returns true if the 
		//C - sting is a match to the SKU code of the Item.
		return strcmp(this->m_sku, sku) == 0;
	}

	bool Item::operator>(const Item& right) const
	{
		//Compares two items alphabetically based on their names.
		return strcmp(this->m_itemname, right.m_itemname) > 0; //wrong, should be based on names
	}

	int Item::operator+=(int quantity)
	{
		//Adds an integer value(right - hand operand) to the quantity and returns the quantity.
		//If the sum of the valueand the quantity exceeds the MAX_STOCK_NUMBER then the quantity 
		//will be set to MAX_STOCK_NUMBERand the Item error will be set to ERROR_POS_QTY.
		this->m_quantity = quantity + this->m_quantity;
		return this->m_quantity;
		if ((quantity + this->m_quantity) > MAX_STOCK_NUMBER)
		{
			this->m_quantity = MAX_STOCK_NUMBER;
			this->m_error = Error(ERROR_POS_QTY);
		}
		//return this->m_quantity;
	}

	int Item::operator--()
	{

		int update = m_quantity - 1;

		if (update < 0)
		{
			m_error = Error("Item out of stock");
			update = 0;
		}

		m_quantity = update;
		return m_quantity;

	}

	int Item::operator-=(int quantity)
	{
		//Reduces the quantity by the right - hand value and returns the quantity.
		//If the value is more than the quantity then the quantity will be set to zero 
		//and the Item error will be set to ERROR_POS_STOCK.
		this->m_quantity= this->m_quantity - quantity;
		return m_quantity;
		if ((this->m_quantity - quantity) > this->m_quantity)
		{
			this->m_quantity = 0;
			this->m_error = Error(ERROR_POS_STOCK);
		}
		//return m_quantity;
	}

	Item::operator bool() const
	{
		//Returns the opposite of the status of the error attribute.
		//This method does not modify the object.
		return !(this->m_error);
	}

	Item& Item::displayType(int POStype)
	{
		//Receives an integer(POS_LIST or POS_FORM) and sets the corresponding attribute.
		//This method returns the reference of the current object.
		// TODO: insert return statement here
		if (POStype == POS_LIST || POStype == POS_FORM)
		{
			this->m_displaytype = POStype;
		}
		return *this;
	}

	double Item::cost() const
	{
		//Returns the cost of the Item; that is the price of the item(plus tax if the item is taxable).
		//This method does not modify the object.
		if (this->m_taxable == true)
		{
			return this->m_price + (this->m_price * TAX);
		}
		else
		{
			return this->m_price;
		}
	}

	int Item::quantity() const
	{
		//Returns the quantity of the Item.This method does not modify the object.
		return this->m_quantity;
	}

	Item& Item::clear()
	{
		//Clears the error status of the objectand then returns the reference of the current object.
		// TODO: insert return statement here
		this->m_error.clear();
		return *this;
	}

	ostream& Item::write(ostream& os) const
	{
		// TODO: insert return statement here
		if(!this->m_error)
		{
			if (this->m_displaytype == POS_LIST)
			{
				os << setw(7) << left << this->m_sku << "|";

				bool flag = strlen(this->m_itemname) > 20;
				switch (flag)
				{
				case true:
					os << string(this->m_itemname, 20) << "|";
					break;
				case false:
					os << setw(20) << left << this->m_itemname << "|";
					break;
				}
				
				os /*<< "|"*/ << setw(7) << right << fixed << setprecision(2) << this->m_price << "|"; //forgot the price which produced unmatched output

				
				switch (this->m_taxable)
				{
				case true:
					os << " X |";
					break;
				case false:
					os << "   |";
					break;
				}
				
				os << setw(4) << right << this->m_quantity << "|";
				os << setw(9) << right << fixed << setprecision(2) << cost() * this->m_quantity << "| "; //forgot fixed everywhere which lead to problems
			}
			else if (this->m_displaytype == POS_FORM)
			{
				os << "=============v\n";
				os << "Name:        " << this->m_itemname << endl;
				os << "Sku:         " << this->m_sku << endl;
				os << "Price:       " << this->m_price << endl;
				os << "Price + tax: ";
				if (this->m_taxable)
				{
					os << fixed << setprecision(2) << cost() << endl;
				}
				else
				{
					os << "N/A" << endl;
				}
				os << "Stock Qty:   " << this->m_quantity << endl;
			}
		}
		else
		{
			os << this->m_error /*<< endl*/; ///////////////////////change
		}
		os << left; //amitoj suggested me this
		return os;
	}

	ofstream& Item::save(ofstream& os) const  
	{
		if (!this->m_error)
		{
			os << itemType() << "," 
				<< this->m_sku << ","
				<< this->m_itemname << ","
				<< fixed << setprecision(2) << this->m_price << ","
				<< int(this->m_taxable) << ","
				<< this->m_quantity;
		}
		else
		{
			cerr << this->m_error << endl; //took reference from ram
		}
		return os;
	}

	istream& Item::read(istream& is)
	{
		
		char sku[MAX_SKU_LEN * 100]{};
		cout << "Sku" << endl; //<< "> "; //had problems printing arrows so had to comment this and get the '>' arrow within the loop
		bool flag = true;
		while (flag)
		{
			cout << "> ";
			is >> sku;
			if (strlen(sku) <= MAX_SKU_LEN)
			{
				flag = false;
				strcpy(this->m_sku, sku);
			}
			else
			{
				cout << ERROR_POS_SKU << endl;
			}
			is.clear();
			is.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		char name[MAX_NAME_LEN * 100]{};
		cout << "Name" << endl; // << "> ";
		flag = true;
		while (flag)
		{
			cout << "> ";
			is.get(name, MAX_NAME_LEN * 100, '\n');
			if (strlen(name) > MAX_NAME_LEN)
			{
				cout << ERROR_POS_NAME << endl;
			}
			else
			{
				flag = false;
				if (this->m_itemname != nullptr)
				{
					delete[] this->m_itemname;
				}
				this->m_itemname = new char[strlen(name) + 1];
				strcpy(this->m_itemname, name);
			}
			is.clear();
			is.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		double price = 0.0;
		cout << "Price" << endl; // << "> ";
		flag = true;
		while (flag)
		{
			cout << "> ";
			if (is >> price && price >= 0)
			{
				flag = false;
			}
			else
			{
				flag = true;
				cout << ERROR_POS_PRICE << endl;
			}
			if (!flag)
			{
				this->m_price = price;
			}
			is.clear();
			is.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		//had a lot of problems in tax, fixed the flag values, 
		//if-else conditions, took a while but got it done somehow
		//used printing debug method to got this done
		char tax[100] = {}; 
		cout << "Taxed?" << endl << "(Y)es/(N)o: ";
		flag = true;
		while (flag)
		{
			//cout << "(Y)es/(N)o: ";
			is >> tax;
			if (strcmp(tax, "y") == 0 || strcmp(tax, "n") == 0)
			{
				flag = false;
				//cout << "1 thissssssssssssssss";
			}
			else
			{
				flag = true;
				//cout << "2 thisssssssssssss";
			}

			if (flag == false && strcmp(tax, "y") == 0)
			{
				this->m_taxable = true;
			}
			else
			{
				this->m_taxable = false;
			}

			if (flag == true)
			{
				cout << "Only 'y' and 'n' are acceptable: ";
			}
			is.clear();
			is.ignore(numeric_limits<streamsize>::max(), '\n');
		}
			
		int q = 0;
		cout << "Quantity" << endl;// << "> ";
		flag = true;
		while (flag)
		{
			cout << "> ";
			is >> q;
			if (q > 0 && q < MAX_STOCK_NUMBER)
			{
				this->m_quantity = q;
				flag = false;
			}
			else
			{
				cout << ERROR_POS_QTY << endl;
				flag = true;
			}
			is.clear();
			is.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		
		return is;

	}

	ifstream& Item::load(ifstream& is) //took reference from ram to get this done
	{
		char sku[MAX_SKU_LEN * 100]{};
		char name[MAX_NAME_LEN * 100];
		double price;
		int tax;
		int q;
		bool flag = true;
		this->clear();

		is.getline(sku, MAX_NAME_LEN * 100, ',');
		is.getline(name, MAX_NAME_LEN * 100, ',');
		is >> price;
		is.ignore();
		is >> tax;
		is.ignore();
		is >> q;

		if (is.fail()) 
		{
			flag = false;
		}
		else
		{
			if (strlen(sku) > MAX_SKU_LEN)
			{
				flag = false;
				this->m_error = ERROR_POS_SKU;
			}
			if (!this->m_error && strlen(name) > MAX_NAME_LEN)
			{
				flag = false;
				this->m_error = ERROR_POS_NAME;
			}
			if (!this->m_error && price < 0)
			{
				flag = false;
				this->m_error = ERROR_POS_PRICE;
			}
			if (!this->m_error && tax != 0 && tax != 1)
			{
				flag = false;
				this->m_error = ERROR_POS_TAX;
			}
			if ((!this->m_error && (q < 0 || q > MAX_STOCK_NUMBER)))
			{
				flag = false;
				this->m_error = ERROR_POS_QTY;
			}
		}

		if (flag) 
		{
			strcpy(this->m_sku, sku);
			if (this->m_itemname != nullptr) 
			{
				delete[] this->m_itemname;
				this->m_itemname = nullptr;
			}
			
			this->m_itemname = new char[strlen(name) + 1];
			strcpy(this->m_itemname, name);
			
			this->m_price = price;
			this->m_taxable = tax;
			this->m_quantity = q;
		}
		return is;
	}

	ostream& Item::bprint(ostream& os) const
	{
		os << "| ";
		
		bool flag = strlen(this->m_itemname) > 20;
		switch (flag)
		{
		case true:
			os << string(this->m_itemname, 20) << "|";
			break;
		case false:
			os << setw(20) << left << this->m_itemname << "|";
			break;
		}

		os << setw(10) << right << fixed << setprecision(2) << cost() << " |  ";
		if (this->m_taxable)
		{
			os << "T  ";
		}
		else
		{
			os << "   ";
		}
		os << "|" << endl;
		return os;
	}

	char* Item::returnsku()
	{
		return this->m_sku;
	}

	//char* Item::returnsku()
	//{
	//	return this->m_sku;
	//}

	double operator+=(double& cost, const Item& item) //doubtful
	{		
		//Overload the operator+= to receive a double reference as the left - hand 
		//operand and a constant reference of Item as the right - hand operator. 
		//This operator should add the product of cost() by quantity() of the Item 
		//to the double operand and then return the value.
		return cost += item.cost() * item.quantity();
	}
}