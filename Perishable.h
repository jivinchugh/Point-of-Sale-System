/*Name: Jivin Chugh
Student id: 156056210
email: jchugh@myseneca.ca
date: 9 April 2023
-------------------------------------------------------------------------------------------------
For this part of milestone, all the work was done by myself, rest I took help from Amitoj in doing
some of the last parts.
-------------------------------------------------------------------------------------------------*/
#pragma once
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include <iostream>
#include "Item.h"
#include "Date.h"

namespace sdds
{
    class Perishable :public Item
    {
    private:
        Date m_expirydate;
    public:
        virtual char itemType()const override;
		
		//read
		std::istream& read(std::istream& is) override;
		
		//write
		std::ostream& write(std::ostream& os)const override;
		
		//load
		std::ifstream& load(std::ifstream& is) override;
		
		//save
		std::ofstream& save(std::ofstream& os)const override;
    };
}
#endif // !SDDS_PERISHABLE_H



