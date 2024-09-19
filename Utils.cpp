/*
Name		: Jivin Chugh
Student id	: 156056210
email		: jchugh@myseneca.ca
date		: 14 March,2023
For milestone part-1, everything was done by myself,
some external references were taken from cplusplus reference
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <limits>
#include <iostream>
#include "Utils.h"
#include "Item.h"
#include "PosApp.h"
using namespace std;
namespace sdds
{
	int validrange(int min, int max, bool rownumber)
	{
		int selection;
		do
		{
			bool flag = true;
			//cin.ignore();
			cin >> selection;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //reference taken from https://cplusplus.com/reference/istream/istream/ignore/
				cout << "Invalid Integer, try again: ";

				selection = -999999; //making selection a random number outside the range instead of using a flag
				//continue;
				flag = false;
			}
			if ((selection < min || selection > max) && flag && rownumber)
			{
				cout << "[" << min << "<=value<=" << max << "], retry: Enter the row number: ";
			}
			if ((selection < min || selection > max) && flag && !rownumber)
			{
				cout << "[" << min << "<=value<=" << max << "], retry: Enter quantity to add: ";
			}
			
		} while (selection < min || selection > max || cin.fail());
		return selection;
	}
	//void sort()
	//{
	//	int i, j;
	//	Item* swap;
	//	//cout << "hereeeeeeeeeeeeeeeeee" << nptr << endl;
	//	for (i = 0; i < nptr - 1; i++)
	//	{
	//		for (j = i + 1; j < nptr; j++)
	//		{
	//			if (*Iptr[i] > *Iptr[j]) //ascending order //wrong, should be based on names
	//			{
	//				swap = Iptr[i];
	//				Iptr[i] = Iptr[j];
	//				Iptr[j] = swap;
	//			}
	//		}
	//	}
	//}
	void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly)
	{
		time_t t = time(NULL);
		tm lt = *localtime(&t);
		day = lt.tm_mday;
		mon = lt.tm_mon + 1;
		year = lt.tm_year + 1900;
		if (dateOnly)
		{
			hour = min = 0;
		}
		else
		{
			hour = lt.tm_hour;
			min = lt.tm_min;
		}
	}


	int uniqueDateValue(int year, int mon, int day, int hour, int min)
	{
		return year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min;
	}

	int daysOfMonth(int year, int month)
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = month >= 1 && month <= 12 ? month : 13;
		mon--;
		return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

}
