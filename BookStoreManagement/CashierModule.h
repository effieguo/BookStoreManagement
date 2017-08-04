#ifndef CashierModule_H
#define CashierModule_H

#include "Module.h"
#include "Array.h"
#include "Book.h"
#include "BookDatabase.h"
#include "HelpFuncs.h"
using namespace std;

/*The Cashier module allows the computer to act as a cash register. The user enters information for the books being purchased and the program calculates 
the sales tax and the total price. In addition, the books being purchased are automatically subtracted from the Inventory Database. */

class CashierModule : public Module
{
private:
	BookDatabase& bookDataBase;

	struct BookPurchaseRequest
	{
		string title;
		int quantity;

		BookPurchaseRequest(const string& ttl = "", const int qty = 1)
			: title(ttl), quantity(qty)
		{

		}
	};

public:
	CashierModule(BookDatabase& db)    //constructor
		: bookDataBase(db)
	{

	}

	void Run() override;
	

private:
	void AddBookToCart(Array<BookPurchaseRequest>& cart);
	

	struct SoldRecord
	{
		std::stringstream printedInfo;
		float subtotal = 0.0f;
		float total = 0.0f;
		float tax = 0.0f;

		SoldRecord()
		{
		}

		void PrintReceipt() const
		{
			// PG 761 in textbook shows good example for formatting
			HelpFuncs::DisplayTitle();
			HelpFuncs::DisplayDate();

			cout << "________________________________________________________________________" << endl;
			cout << left
				<< setw(8) << "Qty"
				<< setw(20) << "ISBN"
				<< setw(20) << "Title"
				<< setw(10) << "Price"
				<< setw(7) << "Total"
				<< endl;
			cout << "_________________________________________________________________________" << endl;

			cout << printedInfo.str();

			cout << endl << endl << endl
				<< right
				<< setw(30) << "Subtotal: " << subtotal << endl
				<< setw(30) << "Tax: " << tax << endl
				<< setw(30) << "Total: " << total << endl;

			cout << endl << endl;
		}
	};

	void CashierModule::CheckOut(const Array<BookPurchaseRequest>& requests, SoldRecord& record);


	bool CalculateBookPrice(const string& title, SoldRecord* pRecord, const int quantity = 1);
};

#endif