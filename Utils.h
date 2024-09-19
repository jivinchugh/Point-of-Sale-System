/*
Name		: Jivin Chugh
Student id	: 156056210
email		: jchugh@myseneca.ca
date		: 14 March,2023
For milestone part-1, everything was done by myself,
some external references were taken from cplusplus reference
*/

#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

namespace sdds
{
	void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);
	int uniqueDateValue(int year, int mon, int day, int hour, int min);
	int daysOfMonth(int year, int month);
	int validrange(int min, int max, bool rownumber);
	//void sort();
}

#endif // !SDDS_UTILS_H
