#define _CRT_SECURE_NO_WARNINGS

#include "ReportModule.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Array.h"
#include "Book.h"
#include "BookDatabase.h"
using namespace std;



void ReportModule::Run()
{
	int selectIndex;
	do
	{
		HelpFuncs::DisplayTitle();
		HelpFuncs::DisplayDate();

		cout << setw(20) << "REPORT MENU" << endl << endl;

		cout << "      " << left << setw(5) << "1." << "Inventory Listing" << endl
			<< "      " << left << setw(5) << "2." << "Inventory Wholesale Value" << endl
			<< "      " << left << setw(5) << "3." << "Inventory Retail Value" << endl
			<< "      " << left << setw(5) << "4." << "Listing by Quantity" << endl
			<< "      " << left << setw(5) << "5." << "Listing by Cost" << endl
			<< "      " << left << setw(5) << "6." << "Listing by Age" << endl
			<< "      " << left << setw(5) << "7." << "Return to the Main Menu" << endl
			<< "      " << left << setw(5) << "Enter Your Choice: ";

		selectIndex = HelpFuncs::GetMenuIndex();

		switch (selectIndex)
		{
		case 1:
			ListInventory();
			break;
		case 2:
			ListWholeSaleValue();
			break;
		case 3:
			ListRetailValue();
			break;
		case 4:
			ListSortedByQuantity();
			break;
		case 5:
			ListSortedByWholeSaleCost();
			break;
		case 6:
			ListSortedByDate();
			break;
		case 7:
			return;
			break;
		default:
			cout << "Invalid input.";
			return;
		}

	} while (selectIndex != 7);
}


void ReportModule::ListInventory()
{
	bookDatabase.ListBookInfo(bookDatabase.GetBookArray(), Book::All);
}

void ReportModule::ListWholeSaleValue()
{
	bookDatabase.ListBookInfo(bookDatabase.GetBookArray(), Book::WholeSaleValue);
}

void ReportModule::ListRetailValue()
{
	bookDatabase.ListBookInfo(bookDatabase.GetBookArray(), Book::RetailValue);
}

void ReportModule::ListSortedByWholeSaleCost()
{
	bookDatabase.ListSortedBookArrayByWholeSaleCost();
}

void ReportModule::ListSortedByQuantity()
{
	bookDatabase.ListSortedBookArrayByQuantity();
}

void ReportModule::ListSortedByDate()
{
	bookDatabase.ListSortedBookArrayByDate();
}
