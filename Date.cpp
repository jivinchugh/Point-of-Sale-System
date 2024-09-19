/*Name: Jivin Chugh
Student id: 156056210
email: jchugh@myseneca.ca
date: 9 April 2023
-------------------------------------------------------------------------------------------------
For this part of milestone, all the work was done by myself, rest I took help from Amitoj in doing
some of the last parts.
-------------------------------------------------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <cstring>
#include <iomanip>
#include "Utils.h"
#include "Error.h"
#include "Date.h"
#include "POS.h"

using namespace std;
namespace sdds
{
	void Date::datevalidation()
	{
		bool flag = true;
		if ((this->m_year < MIN_YEAR || this->m_year > MAX_YEAR) && flag)
		{
			flag = false;
			this->m_successop = Error("Invalid Year");
		}
		else if ((this->m_month < MIN_MONTH || this->m_month > MAX_MONTH) && flag)
		{
			flag = false;
			this->m_successop = Error("Invalid Month");
		}
		else if ((this->m_day < MIN_DAY || this->m_day > daysOfMonth(this->m_year, this->m_month)) && flag)
		{
			flag = false;
			this->m_successop = Error("Invalid Day");
		}
		else if ((this->m_hour < MIN_HOUR || this->m_hour > MAX_HOUR) && flag)
		{
			flag = false;
			this->m_successop = Error("Invalid Hour");
		}
		else if ((this->m_minute < MIN_MINUTE || this->m_minute > MAX_MINUTE) && flag)
		{
			flag = false;
			this->m_successop = Error("Invlid Minute"); //invalid spelling error
		}
		else
		{
			this->m_successop = Error("");
		}
	}



	Date::Date()
	{
		getSystemDate(this->m_year, this->m_month, this->m_day, this->m_hour, this->m_minute, false /*this->m_dateonly*/); //will be set to no date only
		this->m_dateonly = false;
		datevalidation();
	}

	//Date::Date(int year, int month, int day)
	//{
	//	this->m_year = year;
	//	this->m_month = month;
	//	this->m_day = day;
	//	this->m_hour = MIN_HOUR;
	//	this->m_minute = MIN_MINUTE;
	//	this->m_dateonly = true; //set to date only
	//	datevalidation();
	//}

	Date::Date(int year, int month, int day, int hour, int minute)
	{
		this->m_year = year;
		this->m_month = month;
		this->m_day = day;
		this->m_hour = hour;
		this->m_minute = minute;
		
		if (!hour && !minute) //ram helped me with this part
		{
			this->m_dateonly = true;
		}
		else
		{
			this->m_dateonly = /*true*/ false; //not set to date only
		}
		datevalidation();
	}

	bool Date::operator==(const Date& right) const
	{
		return (uniqueDateValue(this->m_year, this->m_month, this->m_day, this->m_hour, this->m_minute) == uniqueDateValue(right.m_year, right.m_month, right.m_day, right.m_hour, right.m_minute));
	}

	bool Date::operator!=(const Date& right) const
	{
		return ((uniqueDateValue(this->m_year, this->m_month, this->m_day, this->m_hour, this->m_minute) != uniqueDateValue(right.m_year, right.m_month, right.m_day, right.m_hour, right.m_minute)));
	}

	bool Date::operator<(const Date& right) const
	{
		return ((uniqueDateValue(this->m_year, this->m_month, this->m_day, this->m_hour, this->m_minute) < uniqueDateValue(right.m_year, right.m_month, right.m_day, right.m_hour, right.m_minute)));
	}

	bool Date::operator>(const Date& right) const
	{
		return ((uniqueDateValue(this->m_year, this->m_month, this->m_day, this->m_hour, this->m_minute) > uniqueDateValue(right.m_year, right.m_month, right.m_day, right.m_hour, right.m_minute)));
	}

	bool Date::operator<=(const Date& right) const
	{
		return ((uniqueDateValue(this->m_year, this->m_month, this->m_day, this->m_hour, this->m_minute) <= uniqueDateValue(right.m_year, right.m_month, right.m_day, right.m_hour, right.m_minute)));
	}

	bool Date::operator>=(const Date& right) const
	{
		return ((uniqueDateValue(this->m_year, this->m_month, this->m_day, this->m_hour, this->m_minute) >= uniqueDateValue(right.m_year, right.m_month, right.m_day, right.m_hour, right.m_minute)));
	}

	

	Date& Date::dateOnly(bool d)
	{
		this->m_dateonly = d;
		if (this->m_dateonly)
		{
			this->m_hour = 0;
			this->m_minute = 0;
		}
		return *this;
	}

	Date::operator bool() const
	{
		return !(this->m_successop);
	}

	const Error& Date::error() const
	{
		return this->m_successop;
	}

	void Date::display(std::ostream& ostr) const //was not sure about how the display function could have been done so was helped by ram in this
	{
		if (!(*this))
		{
			ostr << this->m_successop.displaymessage() 
				 << "(" << this->m_year << "/" << setfill('0') << setw(2) 
				 << this->m_month << "/" << setfill('0') << setw(2) 
				 << this->m_day;
			if (!this->m_dateonly)
			{
				ostr << ", " << setfill('0') << setw(2) << this->m_hour << ":" 
					 << setfill('0') << setw(2) << this->m_minute;
			}
			ostr << ")";
		}
		else
		{
			ostr << right; //amitoj suggested me this
			ostr << this->m_year << "/" << setfill('0') << setw(2)
				 << this->m_month << "/" << setfill('0') << setw(2)
				 << this->m_day;
			if (!this->m_dateonly)
			{
				ostr << ", " << setfill('0') << setw(2) << this->m_hour << ":"
				     << setfill('0') << setw(2) << this->m_minute;
			}
		}
		ostr << left;
		ostr << setfill(' ');
	}

	void Date::read(std::istream& istr)
	{
		this->m_year = 0;
		this->m_month = 0;
		this->m_day = 0;
		this->m_hour = 0;
		this->m_minute = 0;
		this->m_successop.clear();
		bool flag = true;

		if (flag) //year
		{
			//istr.ignore(); //did this mistake because of which it was not printing the year properly, this goes wrong
			istr >> m_year;
			if (istr.fail())
			{
				Error err("Cannot read year entry");
				this->m_successop = err;
				flag = false;
			}
		}

		if(flag) //month
		{
			istr.ignore();
			istr >> m_month;
			if (istr.fail())
			{
				Error err("Cannot read month entry");
				this->m_successop = err;
				flag = false;
			}
		}

		if(flag) //day
		{
			istr.ignore();
			istr >> m_day;
			if (istr.fail())
			{
				Error err("Cannot read day entry");
				this->m_successop = err;
				flag = false;
			}
		}

		if (!this->m_dateonly)
		{
			if (flag) //hour
			{
				istr.ignore();
				istr >> m_hour;
				if (istr.fail())
				{
					Error err("Cannot read hour entry");
					this->m_successop = err;
					flag = false;
				}
			}

			if (flag) //minute
			{
				istr.ignore();
				istr >> m_minute;
				if (istr.fail())
				{
					Error err("Cannot read minute entry");
					this->m_successop = err;
					flag = false;
				}
			}
		}

		if (!this->m_successop)
		{
			datevalidation();
		}
	}

	ostream& operator<<(ostream& os, const Date& rhs)
	{
		// TODO: insert return statement here
		rhs.display(os);
		return os;
	}

	istream& operator>>(istream& is, Date& rhs)
	{
		// TODO: insert return statement here
		rhs.read(is);
		return is;
	}
}