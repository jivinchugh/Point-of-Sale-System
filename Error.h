/*Name: Jivin Chugh
Student id: 156056210
email: jchugh@myseneca.ca
date: 9 April 2023
-------------------------------------------------------------------------------------------------
For this part of milestone, all the work was done by myself, rest I took help from Amitoj in doing
some of the last parts.
-------------------------------------------------------------------------------------------------*/
#ifndef SDDS_ERROR_H
#define SDDS_ERROR_H

#include <iostream>

namespace sdds
{
	class Error
	{
	private:
		char* m_errormessage;
	public:
		Error();
		Error(const char* errormessage);

		//rule of 3
		Error(const Error& err);
		~Error();
		Error& operator=(const Error& err);

		operator bool()const;

		Error& clear();

		//bool errorstate()const; //extra function to comply with the requirement of not creating helper function
		//std::ostream& display(std::ostream& ostr) const; //extra display function
		const char* displaymessage() const;

	};
	std::ostream& operator<<(std::ostream& ostr, const Error& right); //we don't have to use friend, 
	//so we do have to create extra functions
}



#endif // !SDDS_ERROR_H
