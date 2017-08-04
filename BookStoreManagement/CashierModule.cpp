#define _CRT_SECURE_NO_WARNINGS

#include "CashierModule.h"
#include "Module.h"
#include "Array.h"
#include "Book.h"
#include "BookDatabase.h"
#include "HelpFuncs.h"
using namespace std;


void CashierModule::Run()
{
	Array<BookPurchaseRequest> bookCart;

	int selectIndex;
	do
	{
		HelpFuncs::DisplayTitle();


		cout << endl << setw(20) << "CASHIER MENU" << "       ";
		HelpFuncs::DisplayDate();
		cout << endl << endl;

		cout << "      " << left << setw(5) << "1." << "Add book to cart" << endl
			<< "      " << left << setw(5) << "2." << "Checkout" << endl
			<< "      " << left << setw(5) << "3." << "Return to Menu" << endl
			<< "      " << left << setw(5) << "Enter Your Choice: ";

		selectIndex = HelpFuncs::GetMenuIndex();

		switch (selectIndex)
		{
		case 1:
			AddBookToCart(bookCart);
			break;
		case 2:
		{
			SoldRecord record;
			CheckOut(bookCart, record);
			record.PrintReceipt();
			return;

			break;
		}
		case 3:
			return;
			break;
		default:
			cout << "Invalid input.";
			return;
		}

	} while (selectIndex != 3);
}


void CashierModule::AddBookToCart(Array<BookPurchaseRequest>& cart)
{
	BookPurchaseRequest request;

	cout << "Please input the title of the book to add to cart: ";
	getline(cin, request.title);

	cout << "Please input the number of copy you want to purchase: ";
	cin >> request.quantity;

	cart.Add(request);
}


void CashierModule::CheckOut(const Array<BookPurchaseRequest>& requests, SoldRecord& record)
{
	for (int i = 0; i < requests.Size(); i++)
	{
		if (!CalculateBookPrice(requests[i].title, &record, requests[i].quantity))
		{
			cout << endl << "Don't have the requested \"" << requests[i].title << "\" in stock.\n";
		}
	}
	bookDataBase.UpdateBookList("BookData.txt");
}

bool CashierModule::CalculateBookPrice(const string& title, SoldRecord* pRecord, const int quantity/* = 1*/)
{
	const float TAX_RATE = 0.0875f;

	if (bookDataBase.DeleteBook(title, quantity))
	{
		const Book* pBook = bookDataBase.LookUpBook(title);

		float subtotal = pBook->retailPrice * quantity;
		pRecord->subtotal += subtotal;
		pRecord->tax += pRecord->subtotal * TAX_RATE;
		pRecord->total += pRecord->subtotal + pRecord->tax;

		pRecord->printedInfo << setw(2) << quantity
			<< setw(17) << pBook->ISBN
			<< setw(28) << pBook->title
			<< setw(7) << pBook->retailPrice
			<< setw(10) << subtotal
			<< endl;

		return true;
	}

	return false;
}
