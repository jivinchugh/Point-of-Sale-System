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
#include <limits>
#include "Perishable.h"
#include "Date.h"

using namespace std;
namespace sdds
{
	char Perishable::itemType() const
	{
		return 'P';
	}
	istream& Perishable::read(istream& is)
	{
		Item::read(is);
		if (is.good())
		{
			//if the object and the istream are in a good state, 
			//create a local instance of Date and set it to date only.
			Date localdate;
			localdate.dateOnly(this->m_expirydate);
			//then prompt the user as follows
			cout << "Expiry date (YYYY/MM/DD)" << endl;
			cout << "> ";
			is >> localdate; //extract the date from the istream

			//If the date is in a good state 
			if (is.good())
			{
				//set the expiry date to the extracted date
				this->m_expirydate = localdate;
			}
			else
			{
				//if not, set the error object of the Item
				//to the error of the Date.
				Error(ERROR_POS_EMPTY);
			}
		}
		return is;
	}
	ostream& Perishable::write(ostream& os) const
	{
		Item::write(os); //Invoke the write of the base class.
		if(os.good())
		{
			if (this->m_displaytype == POS_LIST)
			{
				/*cout*/ os << " " << this->m_expirydate << " " << "|"; //wrote cout instead of os
			}
			if (this->m_displaytype == POS_FORM)
			{
				if(!m_error)
				/*cout*/ os << "Expiry date: " << this->m_expirydate << "\n" << "=============^" << endl;
			}
		}
		return os;
	}
	ifstream& Perishable::load(ifstream& is)
	{
		Item::load(is); //Invoke the load of the Base class.
		//if the object and the ifstream are in a good state
		if (is.is_open()) //(is.good()) was doing this wrong, wrote is.good() instead of is.is_open()
		{
			//create a local instance of Date and set it to date only.
			Date localdate;
			localdate.dateOnly(this->m_expirydate);
			//Ignore one character to pass the comma
			is.ignore(numeric_limits<streamsize>::max(), ',');
			//Then extract the date from the ifstream
			is >> localdate;
			//If the date is in a good state, 
			if (is.good())
			{
				//set the expiry date to the extracted date
				this->m_expirydate = localdate;
			}
			else
			{
				//if not, set the error object of the Item to the error of the Date
				Error(ERROR_POS_EMPTY);
			}
		}
		return is;
	}
	ofstream& Perishable::save(ofstream& os) const
	{
		//Invoke the save of the Base class.
		Item::save(os);
		if (os.is_open() && os.good()) //If the object is in a good state
		{
			//insert a comma and then the expiry date into ofstream
			os << "," << this->m_expirydate;
		}
		return os;
	}
}