/*Name: Jivin Chugh
Student id: 156056210
email: jchugh@myseneca.ca
date: 9 April 2023
-------------------------------------------------------------------------------------------------
For this part of milestone, all the work was done by myself, rest I took help from Amitoj in doing
some of the last parts.
-------------------------------------------------------------------------------------------------*/
#pragma once
#ifndef SDDS_NONPERISHABLE_H
#define SDDS_NONPERISHABLE_H
#include <iostream>
#include "Item.h"

namespace sdds
{
	class NonPerishable :public Item
	{
	public:
		virtual char itemType()const override;
		std::ostream& write(std::ostream& os)const override;
	};
}
#endif // !SDDS_NONPERISHABLE_H



