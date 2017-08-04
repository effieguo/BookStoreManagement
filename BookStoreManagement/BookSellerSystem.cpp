#define _CRT_SECURE_NO_WARNINGS

#include "Array.h"
#include "Book.h"
#include "BooksellerSystem.h"
#include "BookDatabase.h"
#include "CashierModule.h"
#include "InventoryModule.h"
#include "ReportModule.h"
using namespace std;

BooksellerSystem::~BooksellerSystem()
{
	for (int i = 0; i < modules.Size(); i++)
	{
		if (modules[i])
			delete modules[i];
	}
}

void BooksellerSystem::Initialize(const char* bookData)
{
	bookDataBase.Init(bookData);

	modules.Add(new CashierModule(bookDataBase)); // Index 0
	modules.Add(new InventoryModule(bookDataBase)); // Index 1
	modules.Add(new ReportModule(bookDataBase)); // Index 2
}

void BooksellerSystem::ShowMainMenu()
{
	HelpFuncs::DisplayTitle();

	MenuSelection();
}

void BooksellerSystem::DisplayMainMenu() // ALL WINDOWS SHOULD BE 13 LINES TALL
{
	cout << endl << "             " << "MAIN MENU" << "      ";
	HelpFuncs::DisplayDate();
	cout << endl << endl;

	// PRINTS BLANK SPACE
	cout << "      " << left << setw(5) << "1." << "Cashier Module" << endl
		<< "      " << left << setw(5) << "2." << "Inventory Database Module" << endl
		<< "      " << left << setw(5) << "3." << "Report Module" << endl
		<< "      " << left << setw(5) << "4." << "Exit" << endl << endl
		<< "      " << "Enter Your Choice: ";
}

void BooksellerSystem::MenuSelection()
{
	int moduleIndex;
	do
	{
		DisplayMainMenu();

		// User select modules to run
		moduleIndex = HelpFuncs::GetMenuIndex();

		if (moduleIndex < 1 || moduleIndex > 4)
		{
			cout << "Please enter a index between 1 and 4.\n";
			continue;
		}

		// 1 is Cashier Module
		// 2 is Inventory Database Module
		// 3 is Report Module
		if (moduleIndex != 4)
			modules[moduleIndex - 1]->Run();

	} while (moduleIndex != 4);
}