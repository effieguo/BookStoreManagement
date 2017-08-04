#ifndef InventoryModule_H
#define InventoryModule_H

#include "Module.h"
#include "Array.h"
#include "Book.h"
#include "BookDatabase.h"
#include "HelpFuncs.h"
using namespace std;

/*The Inventory Database will be a file containing a list of all the books in Serendipity’s inventory. 
The informations for each book will be stored in the file.The Inventory module will allow 
the user to look up information on any book in the file, add new books to the file, delete books, and 
change any information in the database.*/


class InventoryModule : public Module
{
private:
	BookDatabase& bookDataBase;

public:
	InventoryModule(BookDatabase& db)        //constructor
		: bookDataBase(db)  
	{
	}

	void Run() override;
	
	void LookUpBook();
	
	void AddBook();
	
	void EditBook();
	
	void DeleteBook();
	

};
#endif