#define _CRT_SECURE_NO_WARNINGS

#include "Module.h"
#include "Array.h"
#include "InventoryModule.h"
#include "Book.h"
#include "BookDatabase.h"
#include "HelpFuncs.h"
using namespace std;


void InventoryModule::Run()
{
	int selectIndex;
	do
	{
		HelpFuncs::DisplayTitle();

		cout << setw(20) << "IVENTORY MENU" << setw(8);
		HelpFuncs::DisplayDate();
		cout << endl << endl;

		// PRINTS BLANK SPACE
		cout << left
			<< "      " << setw(5) << "1." << "Look Up a Book" << endl
			<< "      " << setw(5) << "2." << "Add a Book" << endl
			<< "      " << setw(5) << "3." << "Edit a Book's Record" << endl
			<< "      " << setw(5) << "4." << "Delete a Book" << endl
			<< "      " << setw(5) << "5." << "Return to Main Menu" << endl << endl
			<< "      " << "Enter Your Choice: ";

		selectIndex = HelpFuncs::GetMenuIndex();

		switch (selectIndex)
		{
		case 1:
			LookUpBook();
			break;
		case 2:
			AddBook();
			break;
		case 3:
			EditBook();
			break;
		case 4:
			DeleteBook();
			break;
		case 5:
			return;
			break;
		default:
			cout << "Invalid input." << endl;
			continue;
		}

	} while (selectIndex != 5);
}

void InventoryModule::LookUpBook()
{
	cout << "Please enter the title of the book: ";

	string title;
	getline(cin, title);

	Book* pBook = bookDataBase.LookUpBook(title);
	if (!pBook)
	{
		cout << "The book doesn't exist.\n";
		return;
	}

	HelpFuncs::DisplayTitle();
	cout << setw(24) << "BOOK INFORMATION" << endl << endl;
	pBook->PrintBookInfo();
}

void InventoryModule::AddBook()
{
	Book bookToAdd;

	cout << "Please enter the ISBN of the book: ";
	cin >> bookToAdd.ISBN;
	cin.ignore();

	cout << "Please enter the title of the book: ";
	getline(cin, bookToAdd.title);

	cout << "Please enter the author of the book: ";
	getline(cin, bookToAdd.author);

	cout << "Please enter the publisher of the book: ";
	getline(cin, bookToAdd.publisher);

	cout << "Please enter the date added of the book, month: ";
	cin >> bookToAdd.dateAdded.month;

	cout << "Please enter the date added of the book, day: ";
	cin >> bookToAdd.dateAdded.day;

	cout << "Please enter the date added of the book, year: ";
	cin >> bookToAdd.dateAdded.year;

	cout << "Please enter the quantity of the book: ";
	cin >> bookToAdd.quantityOnHand;

	cout << "Please enter the wholesale cost of the book: ";
	cin >> bookToAdd.wholeSaleCost;

	cout << "Please enter the retail price of the book: ";
	cin >> bookToAdd.retailPrice;

	bookDataBase.AddBook(bookToAdd, bookToAdd.quantityOnHand);
	bookDataBase.UpdateBookList("BookData.txt");
}

void InventoryModule::EditBook()
{
	cout << endl << "Please enter the title of the book you want to edit: " << endl;

	string title;
	getline(cin, title);

	Book* pBook = bookDataBase.LookUpBook(title);

	if (!pBook)
	{
		cout << endl << "The book does not exist" << endl;
		return;
	}

	cout << endl << "What would you like to edit? " << endl;
	cout << "1. ISBN\n";
	cout << "2. Title:\n";
	cout << "3. Author\n";
	cout << "4. Publisher\n";
	cout << "5. Date Added\n";
	cout << "6. Quantity\n";
	cout << "7. Wholesale Cost\n";
	cout << "8. Retail Price\n";
	cout << "Please select item:";

	int index;
	index = HelpFuncs::GetMenuIndex();

	string item;
	BookDatabase::EditValue editVal;
	switch (index)
	{
	case 1:
		item = "ISBN";
		cout << "Please enter the new ISBN: ";
		cin >> editVal.Longlong;
		break;
	case 2:
		item = "title";
		cout << "Please enter the new Title: ";
		cin.ignore();
		getline(cin, editVal.String);
		break;
	case 3:
		item = "author";
		cout << "Please enter the new Author: ";
		cin.ignore();
		getline(cin, editVal.String);
		break;
	case 4:
		item = "publisher";
		cout << "Please enter the new Publisher: ";
		cin.ignore();
		getline(cin, editVal.String);
		break;
	case 5:
		item = "dateAdded";
		int month, day, year;
		cout << "Please enter the new Month: ";
		cin >> month;
		cout << "Please enter the new Day: ";
		cin >> day;
		cout << "Please enter the new Year: ";
		cin >> year;
		editVal._Date = Date(month, day, year);
		break;
	case 6:
		item = "quantity";
		cout << "Please enter the new Quantity: ";
		cin >> editVal.Integer;
		break;
	case 7:
		item = "wholeSaleCost";
		cout << "Please enter the new WholesaleCost: ";
		cin >> editVal.Float;
		break;
	case 8:
		item = "retailPrice";
		cout << "Please enter the new RetailPrice: ";
		cin >> editVal.Float;
		break;
	default:
		cout << "Invalid input.";
		return;
	}
	bookDataBase.EditBook(title, item, editVal);
	bookDataBase.UpdateBookList("BookData.txt");
}

void InventoryModule::DeleteBook()
{
	string bookTitle;
	int quantity;
	cout << "Enter the book title you want delete: ";
	getline(cin, bookTitle);
	cout << "Enter the number of copy you want delete: ";
	cin >> quantity;
	bookDataBase.DeleteBook(bookTitle, quantity);
	bookDataBase.UpdateBookList("BookData.txt");

}

