/*Name: Jivin Chugh
Student id: 156056210
email: jchugh@myseneca.ca
date: 9 April 2023
-------------------------------------------------------------------------------------------------
For this part of milestone, all the work was done by myself, rest I took help from Amitoj in doing
some of the last parts.
-------------------------------------------------------------------------------------------------*/
#ifndef SDDS_POS_H
#define SDDS_POS_H

namespace sdds
{
	const double TAX = 0.13;
	const int MAX_SKU_LEN = 7;

	const int MIN_YEAR = 2000;
	const int MAX_YEAR = 2030;

	const int MAX_STOCK_NUMBER = 99;
	const int MAX_NO_ITEMS = 200;

	const int MIN_MONTH = 1;
	const int MAX_MONTH = 12;

	const int MIN_DAY = 1;
	//const int MAX_DAY = 31; we have to use function

	const int MIN_HOUR = 0;
	const int MAX_HOUR = 23;

	const int MIN_MINUTE = 0;
	const int MAX_MINUTE = 59;

	const int MAX_NAME_LEN = 40;
	
	const int POS_LIST = 1;
	const int POS_FORM = 2;


	const char ERROR_POS_SKU[] = "SKU too long";
	const char ERROR_POS_NAME[] = "Item name too long";
	const char ERROR_POS_PRICE[] = "Invalid price value";
	const char ERROR_POS_TAX[] = "Invalid tax status";
	const char ERROR_POS_QTY[] = "Invalid quantity value";
	const char ERROR_POS_STOCK[] = "Item out of stock";
	const char ERROR_POS_EMPTY[] = "Invalid Empty Item";


}

#endif // !SDDS_POS_H
