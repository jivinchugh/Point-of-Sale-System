/*
Name		: Jivin Chugh
Student id	: 156056210
email		: jchugh@myseneca.ca
date		: 16 April,2023
For milestone part, everything was done by myself; amitoj helped me in part 5 a bit (POS function)
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <limits>
#include <iomanip>
#include "Perishable.h"
#include "NonPerishable.h"
#include "PosApp.h"
#include "Utils.h"
#include "Bill.h"
using namespace std;
namespace sdds
{
	/*PosApp::PosApp()
	{
		strcpy(m_filename, "");
		m_copyobject = false;
	}*/

	void PosApp::action(const char* title)
	{
		cout << ">>>> " << left << setw(72) << setfill('.') << title << endl;
	}

	void PosApp::sort()
	{
		int i, j;
		Item* swap;
		//cout << "hereeeeeeeeeeeeeeeeee" << nptr << endl;
		for (i = 0; i < nptr - 1; i++)
		{
			for (j = i + 1; j < nptr; j++)
			{
				if (*Iptr[i] > *Iptr[j]) //ascending order //wrong, should be based on names //Item.cpp was wrong
				{
					swap = Iptr[i];
					Iptr[i] = Iptr[j];
					Iptr[j] = swap;
				}
			}
		}
	}

	PosApp::PosApp(const char* filename)
	{
		if(filename!=nullptr && filename[0]!='\0')
		{
			strncpy(this->m_filename, filename, 127);
			this->m_filename[127] = '\0';
		}
		else
		{
			this->m_filename[0] = '\0';
		}
		nptr = 0;
		int i = 0;
		for (i = 0; i < MAX_NO_ITEMS; i++)
		{
			Iptr[i] = nullptr;
		}
		//m_copyobject = false;
	}
	
	bool PosApp::menu() //return value for menu was initialized as void first but then i thought bool would make things much easier
	{
		int selection;
		bool flag = true;
		cout << "The Sene-Store" 
				<< endl <<
				"1- List items" 
				<< endl <<
				"2- Add item" 
				<< endl <<
				"3- Remove item" 
				<< endl <<
				"4- Stock item" 
				<< endl <<
				"5- POS" 
				<< endl <<
				"0- exit program" 
				<< endl <<
				"> ";
		
		selection = validrange(0, 5, true);
		switch (selection)
		{
		case 1:
			listItems(true);
			break;
		case 2:
			addItem();
			break;
		case 3:
			removeItem();
			break;
		case 4:
			stockItem();
			break;
		case 5:
			POS();
			break;
		default: //let us suppose 0
			saveRecs();
			cout << "Goodbye!" << endl;
			flag = false;
			break;
		}
		return flag;
	}
	void PosApp::addItem()
	{
		//Print the action title Adding Item to the store.
		cout << ">>>> Adding Item to the store................................................" << endl;

		//if the number of items is at maximum, print "Inventory Full!" and exit the function.
		if (nptr >= MAX_NO_ITEMS)
		{
			//if the number of items is at maximum, print "Inventory Full!" and exit the function.
			cout << "Inventory Full!" << endl;
			return;
		}
		else
		{
			//if not, create a pointer to an item and ask the user if the item is perishable
			
			cout << "Is the Item perishable? (Y)es/(N)o: ";
			char c = '\0';
			cin >> c;
			cin.ignore();
			//Item* item = nullptr;
			/*Iptr[nptr] = item;
			nptr++;*/
			//char c = '\0';
			bool loop = true;
			while (loop/*(c != 'Y' && c != 'y') || (c != 'N' && c != 'n')*/) //loop for a yes or no
			{
				//Based on the user's answer dynamically create an instance of an Item 
				//(Perishable or NonPerishable)
				//and keep the address in the Item pointer
				//if not, create a pointer to an item and ask the user if the item is perishable
				Item* item = nullptr;
				if (c == 'Y' || c == 'y')
				{
					loop = false;
					item = new Perishable();
				}
				else if (c == 'N' || c == 'n')
				{
					loop = false;
					item = new NonPerishable();
				}
				else
				{
					loop = true;
					cout << ", try again..." << endl;
				}
				if (item->read(cin))
				{
					if (nptr < MAX_NO_ITEMS)
					{
						cout << ">>>> DONE!..................................................................." << endl;
						Iptr[nptr] = item;
						nptr++;
					}
					else
					{
						cout << "Inventory Full!" << endl;
					}
				}
				else
				{
					delete item;
				}
				//cin.ignore();
			}
			//cout << ">>>> DONE!..................................................................." << endl;
			//delete item;
		}
		//delete item;
		
	}
	void PosApp::removeItem()
	{
		//cout << ">>>> Remove Item............................................................." << endl;
		//cout << "Running removeItem()" << endl;
		//Print the action title Remove Item.
		action("Remove Item");
		//call the selectItem to get the row number of the Item
		//(row number is index + 1 in Iptr array)
		int row;
		row = selectItem();
		//print Removing.... 
		cout << "Removing...." << endl;
		//and show the item that is about to be removed in POS_FROM format.
		cout << Iptr[row - 1]->displayType(POS_FORM);
		//deallocate and remove the item from the Iptr array (see illustration)
		delete Iptr[row - 1];
		//keeping items one number back so as to remove the empty space
		for (int i = row; i < nptr; i++)
		{
			Iptr[i - 1] = Iptr[i];
		}
		--nptr; //deducting as one of the item is removed // I forgot to do this
		//printing done
		cout<<">>>> DONE!..................................................................." << endl;
	}
	void PosApp::stockItem()
	{
		//cout << ">>>> Select an item to stock................................................." << endl;
		//cout << "Running stockItem()" << endl;
		//Print the action title Select an item to stock.
		action("Select an item to stock");
		//call the seletItem method and get the row number
		int row;
		row = selectItem();
		//Print Selected Item:\n
		cout << "Selected Item:\n";
		//display the select Item
		Item* item = Iptr[row - 1];
		//Item will be displayed on the screen in POS_FORM format
		cout << Iptr[row - 1]->displayType(POS_FORM);
		//Prompt Enter quantity to add: 
		cout << "Enter quantity to add: ";
		int q = 0;
		q = validrange(1, MAX_STOCK_NUMBER - Iptr[row - 1]->quantity(), false);
		*item += q;
		cout << ">>>> DONE!..................................................................." << endl;

	}
	void PosApp::listItems(bool flag)
	{
		cout.fill(' ');
		//Print the action title Listing Items.
		cout << ">>>> Listing Items..........................................................." << endl;
		//cout << "Running listItems()" << endl;
		
		//Sort all the Items in Iptr array based on their name in ascending order.
		sort();
		//int i, j;
		//Item* swap;
		//for (i = 0; i < nptr - 1; i++)
		//{
		//	for (j = i + 1; j < nptr; j++)
		//	{
		//		if (*Iptr[j] < *Iptr[i]) //ascending order
		//		{
		//			swap = Iptr[i];
		//			Iptr[i] = Iptr[j];
		//			Iptr[j] = swap;
		//		}
		//	}
		//}

		//Print the Title/Header of the list:
		cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl;
		cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;
		//Loop through the items up to nptr
		int total = 0;
		for (int i = 0; i < nptr; i++)
		{
			//display the row and the Items in POS_LIST format
			cout << right << setw(4) << i + 1 << " | ";
			Iptr[i]->displayType(POS_LIST);
			cout << *(Iptr[i]) << endl;
			//int total = 0;
			total += Iptr[i]->cost() * Iptr[i]->quantity();
		}
		cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
		if (flag == true)
		{
			cout << "                               Total Asset: $  |       " << total << "| " << endl;
			cout << "-----------------------------------------------^--------------^" << endl << endl;
		}
		//cout << endl;
	}
	void PosApp::POS()
	{
		//cout << ">>>> Starting Point of Sale.................................................." << endl;
		//cout << "Running POS()" << endl;
		//Print the action title Starting Point of Sale.
		action("Starting Point of Sale");
		char sku[MAX_SKU_LEN];
		//cin.clear();
		//cout << "Enter SKU or <ENTER> only to end sale..." << endl << "> ";
		//cin.getline(sku, MAX_SKU_LEN);
		double /*int*/ /*q,*/ total = 0.0;
		bool flag = true;
		Bill newbill;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		//Item* item = nullptr;
		//strncpy(sku, returnsku, MAX_SKU_LEN + 1);
		//cin.clear();
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		//if SKU is not empty end the istream is not in a fail state
		/*while (sku[0] != '\0' && !cin.fail())
		{

		}*/
		do
		{
			cout << "Enter SKU or <ENTER> only to end sale..." << endl << "> ";
			//cin.clear();

			//cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.getline(sku, MAX_SKU_LEN, '\n');
			if (sku[0] == '\0')
			{
				flag = false;
			}
			else
			{
				Item* item = search(sku);
				if (item == nullptr)
				{
					cout << "!!!!! Item Not Found !!!!!" << endl;
				}
				else //(item != nullptr)
				{
					if (item->quantity() == 0)
					{
						cout << "Item out of stock" << endl;
					}
					else
					{
						--* item; //amitoj gave me a hint of this
						if (*item)
						{
							cout << item->displayType(POS_FORM) << endl;
							newbill.add(item);
							total += item->cost();
							cout << ">>>>> Added to bill" << endl;
							//cout << fixed << setprecision(2);
							cout << ">>>>> Total: " << fixed << setprecision(2) << total << endl;
						}
						else
						{
							cin.clear();
						}
					}
				}
			}
			
		} while (flag && !cin.fail());
		newbill.print(cout);
	}

	Item* PosApp::search(char* searchsku)
	{
		int i = 0;
		for (i = 0; i < this->nptr; i++)
		{
			if (strcmp(Iptr[i]->returnsku(), searchsku) == 0)
			{
				return this->Iptr[i];
			}
		}
		return nullptr;
	}

	void PosApp::saveRecs()
	{
		//Print the action title Saving Data.
		cout << ">>>> Saving Data............................................................." << endl;
		//cout << "Saving data in " << m_filename << endl;

		//Create an instance of ofstream using the data filename.
		ofstream os(this->m_filename);
		//loop through the Items pointed by the Iptr pointers and 
		for (int i = 0; i < nptr; i++)
		{
			//insert them into the ofstream instance up to nptr
			os << *Iptr[i] << endl;
		}
		os.close();
	}
	void PosApp::loadRecs()
	{
		//Print the action title Loading Items.
		cout << ">>>> Loading Items..........................................................." << endl;
		//cout << "Loading data from " << m_filename << endl;
		//open the data file in an ifstream object (we will call this input here).
		ifstream is(this->m_filename);

		//if opening the file was not successful
		if (is.fail())
		{
			//create the file by opening 
			ofstream os(this->m_filename);
			//and closing it using an ofstream object.
			os.close();
		}

		//empty the posApp class, make sure there are no items in Iptr
		for (int i = 0; i < nptr; i++) //amitoj helped me in this
		{
			delete Iptr[i];
			Iptr[i] = nullptr;
		}
		nptr = 0;

		//while the input is in a good state and the Iptr array is not full
		while (is.good() && nptr < MAX_NO_ITEMS)
		{
			char c = '\0';
			//read one character
			is >> c;

			if (is.good())
			{
				//create a dynamic Item (either Perishable, or NonPershable) 
				//based on the character being P or N and 
				//keep the address in the next available Iptr pointer
				Item *item = nullptr;
				if (c == 'P')
				{
					item = new Perishable();
				}
				if (c == 'N')
				{
					item = new NonPerishable();
				}
				if (item != nullptr) //ram helped me over here
				{
					is.ignore();
					item->load(is);
					//keeping address in next available iptr pointer
					Iptr[nptr] = item;
					nptr++;
				}
			}
		}
		is.close();
	}
	int PosApp::selectItem()
	{
		//Print the action title Item Selection by row number.
		action("Item Selection by row number");
		cout << "Press <ENTER> to start....";
		cin.get();
		cin.ignore(numeric_limits<streamsize>::max(), '\n' /*','*/);
		listItems(false); //for this I had to change the deifinition of listItems to accept a bool
		//setting false coz total assets was not supposed to be printed
		cout << "Enter the row number: ";
		int row = 0; 
		//bool flag = true;
		row = validrange(1, nptr, true);
		//while (row < 1 || row > nptr)
		//{
		//	while (!(cin >> row))
		//	{
		//		cout << "Invalid Integer, try again: ";
		//		cin.clear();
		//		cin.ignore(numeric_limits<streamsize>::max(), '\n'/*','*/);
		//	}
		//	if (row < 1 || row > nptr)
		//	{
		//		cout << "[1<=value<=" << nptr << "], retry: Enter the row number: ";
		//	}
		//}
		return row;
	}
	int PosApp::run()
	{
		loadRecs();
		bool check = true;
		do
		{
			check = menu();
		} while (check);
		return 0;
	}
	PosApp::~PosApp()
	{
		for (int i = 0; i < nptr; i++)
		{
			delete Iptr[i];
			Iptr[i] = nullptr;
		}
	}
}
