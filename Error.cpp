/*Name: Jivin Chugh
Student id: 156056210
email: jchugh@myseneca.ca
date: 9 April 2023
-------------------------------------------------------------------------------------------------
For this part of milestone, all the work was done by myself, rest I took help from Amitoj in doing
some of the last parts.
-------------------------------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Error.h"

using namespace std;
namespace sdds
{
	Error::Error()
	{
		//clear();
		this->m_errormessage = nullptr;
	}

	Error::Error(const char* errormessage)
	{
		//The Error class can also get created using an 
		//error message (a C-string). In this case, the 
		//Error object will be in an erroneous state.
		bool notempty = errormessage && strlen(errormessage);
		if (notempty)
		{
			this->m_errormessage = new char[strlen(errormessage) + 1];
			strcpy(this->m_errormessage, errormessage);
		}
		else
		{
			this->m_errormessage = nullptr;
		}
	}

	Error::Error(const Error& err)
	{
		bool notempty = err.m_errormessage && strlen(err.m_errormessage);
		if (notempty)
		{
			this->m_errormessage = new char[strlen(err.m_errormessage) + 1];
			strcpy(this->m_errormessage, err.m_errormessage);
		}
		else
		{
			this->m_errormessage = nullptr;
		}
	}

	Error::~Error()
	{
		clear();
	}

	Error& Error::operator=(const Error& err)
	{
		clear();
		bool notempty = err.m_errormessage && strlen(err.m_errormessage);
		if (notempty)
		{
			this->m_errormessage = new char[strlen(err.m_errormessage) + 1];
			strcpy(this->m_errormessage, err.m_errormessage);
		}
		return *this;
	}

	Error::operator bool() const
	{
		//If an Error object is casted to a bool, 
		//it should return true if the message is
		//not null and false if it is null.
		return m_errormessage && strlen(m_errormessage);
	}

	Error& Error::clear()
	{
		//This method clears the error message and returns the
		//reference of the current Error object.After this, 
		//the Error object should be in an "no Error" state with 
		//the message set to nullptr;
		delete[] m_errormessage;
		m_errormessage = nullptr;
		return *this;
	}

	//bool Error::errorstate() const
	//{
	//	if (this->m_errormessage != nullptr && this->m_errormessage[0] != '\0')
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}

	//ostream& Error::display(ostream& ostr) const
	//{
	//	// TODO: insert return statement here
	//	if (this->m_errormessage)
	//	{
	//		ostr << this->m_errormessage;
	//	}
	//	return ostr;
	//}

	const char* Error::displaymessage() const
	{
		return this->m_errormessage;
	}

	ostream& operator<<(ostream& ostr, const Error& right)
	{
		//why can't we call the bool operator ovverloading function here
		if (right.displaymessage())
		{
			ostr << right.displaymessage();
		}
		return ostr;
	}

}

