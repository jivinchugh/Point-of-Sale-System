/*Name: Jivin Chugh
Student id: 156056210
email: jchugh@myseneca.ca
date: 9 April 2023
-------------------------------------------------------------------------------------------------
For this part of milestone, all the work was done by myself, rest I took help from Amitoj in doing
some of the last parts.
-------------------------------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include "PosIO.h"

using namespace std;

namespace sdds
{
	ostream& operator<<(ostream& os, const PosIO& right)
	{
		// TODO: insert return statement here
		return right.write(os);
	}
	ofstream& operator<<(ofstream& os, const PosIO& right)
	{
		// TODO: insert return statement here
		return right.save(os);
	}
	istream& operator>>(istream& is, /*const*/ PosIO& right)
	{
		// TODO: insert return statement here
		return right.read(is);
	}
	ifstream& operator>>(ifstream& is, /*const*/ PosIO& right)
	{
		// TODO: insert return statement here
		return right.load(is);
	}
}