#ifndef BooksellerSystem_H
#define BooksellerSystem_H

#include "Array.h"
#include "Book.h"
#include "BookDatabase.h"
#include "CashierModule.h"
#include "InventoryModule.h"
#include "ReportModule.h"
using namespace std;



class BooksellerSystem     //When the program runs, a menu will be displayed on the screen, which allows the user to activate any of the modules. 
{
private:
	BookDatabase bookDataBase;
	Array<Module*> modules;
	Date date;

public:
	~BooksellerSystem();

	void Initialize(const char* bookData);
	
	void ShowMainMenu();
	
private:
	void DisplayMainMenu(); // ALL WINDOWS SHOULD BE 13 LINES TALL
	

	void MenuSelection();
	
};
#endif