/*Name: Jivin Chugh
Student id: 156056210
email: jchugh@myseneca.ca
date: 9 April 2023
-------------------------------------------------------------------------------------------------
For this part of milestone, all the work was done by myself, rest I took help from Amitoj in doing
some of the last parts.
-------------------------------------------------------------------------------------------------*/
#ifndef SDDS_POSIO_H
#define SDDS_POSIO_H

#include <fstream>
#include <iostream>

namespace sdds
{
	class PosIO
	{
	public:
		virtual ~PosIO() {};
		virtual std::ostream& write(std::ostream& os)const = 0;
		virtual std::istream& read(std::istream& is) = 0;
		virtual std::ofstream& save(std::ofstream& os)const = 0;
		virtual std::ifstream& load(std::ifstream& is) = 0;
	};

	std::ostream& operator<<(std::ostream& os, const PosIO& right);
	std::ofstream& operator<<(std::ofstream& os, const PosIO& right);

	std::istream& operator>>(std::istream& is, /*const*/ PosIO& right);
	std::ifstream& operator>>(std::ifstream& is, /*const*/ PosIO& right);
}

#endif // !SDDS_POSIO_H
