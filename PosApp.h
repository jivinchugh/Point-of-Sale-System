/*
Name		: Jivin Chugh
Student id	: 156056210
email		: jchugh@myseneca.ca
date		: 15 April,2023
For milestone part, everything was done by myself,
*/

#ifndef SDDS_POSAPP_H
#define SDDS_POSAPP_H
#include "Item.h"
namespace sdds
{
	class PosApp
	{
		char m_filename[128];
		Item* Iptr[MAX_NO_ITEMS];
		int nptr;
		void action(const char* title);
		void sort();
		//bool m_copyobject;
		
	public:
		//PosApp();
		PosApp(const char* filename);
		bool menu();
		void addItem();
		void removeItem();
		void stockItem();
		void listItems(bool flag);
		void POS();
		void saveRecs();
		void loadRecs();
		int selectItem();
		int run();
		PosApp(const PosApp& /*rhs*/) = delete;
		PosApp& operator=(const PosApp&) = delete; //a little bit doubtful about the implementation of this
		~PosApp();

		Item* search(char* searchsku);
	};
}


#endif //SDDS_POSAPP_H
