/*Name: Jivin Chugh
Student id: 156056210
email: jchugh@myseneca.ca
date: 9 April 2023
-------------------------------------------------------------------------------------------------
For this part of milestone, all the work was done by myself, rest I took help from Amitoj in doing
some of the last parts.
-------------------------------------------------------------------------------------------------*/

#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include <iostream>
#include "Error.h"

namespace sdds
{
	class Date
	{
	private:
		int m_year;
		int m_month;
		int m_day;
		int m_hour;
		int m_minute;
		bool m_dateonly;
		Error m_successop; //success operation

		void datevalidation();
		
	public:
		Date();
		//Date(int year, int month, int day);
		Date(int year, int month, int day, int hour = 0, int minute = 0);

		bool operator==(const Date& right)const;
		bool operator!=(const Date& right)const;
		bool operator<(const Date& right)const;
		bool operator>(const Date& right)const;
		bool operator<=(const Date& right)const;
		bool operator>=(const Date& right)const;

		Date& dateOnly(bool d);
		
		operator bool() const;

		const Error& error() const;

		void display(std::ostream& ostr)const;
		void read(std::istream& istr);
	};
	std::ostream& operator<<(std::ostream& os, const Date& rhs);
	std::istream& operator>>(std::istream& is, Date& rhs);
}

#endif // !SDDS_DATE_H
