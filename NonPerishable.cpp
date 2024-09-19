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
#include "NonPerishable.h"

using namespace std;
namespace sdds
{
	char NonPerishable::itemType() const
	{
		return 'N';
	}
	ostream& NonPerishable::write(ostream& os) const
	{
		Item::write(os);
		if (os.good())
		{
			if (this->m_displaytype == POS_LIST)
			{
				os << "    N / A   |";
			}
			if (this->m_displaytype == POS_FORM)
			{
				if(!this->m_error)
				os << "=============^" << endl;
			}
		}
		return os;
	}
}