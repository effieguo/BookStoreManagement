#define _CRT_SECURE_NO_WARNINGS

#include "BookDatabase.h"
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Array.h"
#include "Book.h"
using namespace std;


void BookDatabase::Init(const char* fileName)
{
	ifstream inFile;
	try
	{
		inFile.open(fileName);
	}
	catch (std::exception &ex)
	{
		cout << "Can not open " << fileName << endl;
	}

	while (!inFile.eof())
	{
		if (inFile.eof())
			break;

		Book bookToAdd;
		inFile >> bookToAdd;

		inFile.ignore();

		books.Add(bookToAdd);
	}
}

Array<Book> BookDatabase::GetBookArray()
{
	return books;
}

const Array<Book>& BookDatabase::GetBookArray() const
{
	return books;
}

void BookDatabase::AddBook(const Book& book, const int quantity/* = 1*/) // book should be initialized, including the dateAdded member
{
	const string& title = book.title;

	Book* pBook = LookUpBook(title);
	if (pBook)
	{
		pBook->quantityOnHand += quantity;
		return;
	}

	// If this is a new book
	books.Add(book);
	books.Last().quantityOnHand = quantity;
}


bool BookDatabase::DeleteBook(const string& title, const int quantity/* = 1*/)
{
	Book* pBook = LookUpBook(title);
	if (pBook)
	{
		if (pBook->quantityOnHand >= quantity)
		{
			// Found the book in stock and we have enough quantity
			pBook->quantityOnHand -= quantity;
			return true;
		}
		else
		{
			// Don't have enough quantity at hand
			return false;
		}
	}

	// Don't have the requested book in stock
	return false;
}

bool BookDatabase::DeleteBook(const long long ISBN, const int quantity/* = 1*/)
{
	Book* pBook = LookUpBook(ISBN);
	if (pBook)
	{
		if (pBook->quantityOnHand >= quantity)
		{
			// Found the book in stock and we have enough quantity
			pBook->quantityOnHand -= quantity;
			return true;
		}
		else
		{
			// Don't have enough quantity at hand
			return false;
		}
	}

	// Don't have the requested book in stock
	return false;
}

void BookDatabase::EditBook(const string& title, const string& editItem, EditValue& val)
{
	Book* pBook = LookUpBook(title);

	if (editItem == "ISBN")
	{
		pBook->ISBN = val.Longlong;
	}
	if (editItem == "title")
	{
		pBook->title = val.String;
	}
	else if (editItem == "author")
	{
		pBook->author = val.String;
	}
	else if (editItem == "publisher")
	{
		pBook->publisher = val.String;
	}
	else if (editItem == "dateAdded")
	{
		pBook->dateAdded = val._Date;
	}
	else if (editItem == "wholeSaleCost")
	{
		pBook->wholeSaleCost = val.Float;
	}
	else if (editItem == "retailPrice")
	{
		pBook->retailPrice = val.Float;
	}
	else if (editItem == "quantity")
	{
		pBook->quantityOnHand = val.Integer;
	}

}

void BookDatabase::EditBook(const long long ISBN, const string& editItem, EditValue& val)
{
	Book* pBook = LookUpBook(ISBN);

	if (editItem == "title")
	{
		pBook->title = val.String;
	}
	else if (editItem == "author")
	{
		pBook->author = val.String;
	}
	else if (editItem == "publisher")
	{
		pBook->publisher = val.String;
	}
	else if (editItem == "dateAdded")
	{
		pBook->dateAdded = val._Date;
	}
	else if (editItem == "wholeSaleCost")
	{
		pBook->wholeSaleCost = val.Float;
	}
	else if (editItem == "retailPrice")
	{
		pBook->retailPrice = val.Float;
	}
	else if (editItem == "quantity")
	{
		pBook->quantityOnHand = val.Integer;
	}

}

	// Get the book pointer based on a given title

Book* BookDatabase::LookUpBook(const string& title)
{
	for (int i = 0; i < books.Size(); i++)
	{
		if (books[i].title == title)
			return &books[i];
	}

	return nullptr;
}

const Book* BookDatabase::LookUpBook(const string& title) const
{
	for (int i = 0; i < books.Size(); i++)
	{
		if (books[i].title == title)
			return &books[i];
	}

	return nullptr;
}

Book* BookDatabase::LookUpBook(const long long ISBN)
{
	for (int i = 0; i < books.Size(); i++)
	{
		if (books[i].ISBN == ISBN)
			return &books[i];
	}

	return nullptr;
}

const Book* BookDatabase::LookUpBook(const long long ISBN) const
{
	for (int i = 0; i < books.Size(); i++)
	{
		if (books[i].ISBN == ISBN)
			return &books[i];
	}

	return nullptr;
}

void BookDatabase::UpdateBookList(const char* fileName) const
{
	ofstream outFile(fileName);

	for (int i = 0; i < books.Size(); i++)
	{
		outFile << books[i].ISBN << " "
			<< "\"" << books[i].title << "\" "
			<< "\"" << books[i].author << "\" "
			<< "\"" << books[i].publisher << "\" "
			<< books[i].dateAdded.month << " "
			<< books[i].dateAdded.day << " "
			<< books[i].dateAdded.year << " "
			<< books[i].wholeSaleCost << " "
			<< books[i].retailPrice << " "
			<< books[i].quantityOnHand;
		
		if(i < books.Size() - 1)
			outFile << endl;
	}

	outFile.close();
}

void BookDatabase::ListBookInfo(const Array<Book>& bookArray, const Book::ListKey key)
{
	float totalWholeSaleValue = 0.0f;
	float totalRetailValue = 0.0f;
	for (int i = 0; i < bookArray.Size(); i++)
	{
		cout << "Book " << i+1 << ":\n";
		bookArray[i].PrintBookInfo(key);
		cout << endl;

		if (key & Book::WholeSaleValue)
			totalWholeSaleValue += bookArray[i].wholeSaleCost;

		if (key & Book::RetailValue)
			totalRetailValue += bookArray[i].retailPrice;
	}

	if (key & Book::WholeSaleValue)
		cout << "Total Whole Sale Value: " << totalWholeSaleValue << endl;

	if (key & Book::RetailValue)
		cout << "Total Retail Value: " << totalRetailValue << endl;
}

void BookDatabase::ListSortedBookArrayByRetailPrice()
{
// Make a copy of the book array
	Array<Book> sortedBooks = GetBookArray();

	struct LessThan_Price
	{
		bool operator () (const Book& lhs, const Book& rhs) const
		{
			return lhs.retailPrice < rhs.retailPrice;
		}
	};

	LessThan_Price funcObj;
	sortedBooks.Sort(funcObj);

	ListBookInfo(sortedBooks);
}

void BookDatabase::ListSortedBookArrayByWholeSaleCost()
{
	// Make a copy of the book array
	Array<Book> sortedBooks = GetBookArray();

	struct LessThan_Cost
	{
		bool operator () (const Book& lhs, const Book& rhs) const
		{
			return lhs.wholeSaleCost < rhs.wholeSaleCost;
		}
	};

	LessThan_Cost funcObj;
	sortedBooks.Sort(funcObj);

	ListBookInfo(sortedBooks);
}

void BookDatabase::ListSortedBookArrayByQuantity()
{
	// Make a copy of the book array
	Array<Book> sortedBooks = GetBookArray();

	struct LessThan_Quantity
	{
		bool operator () (const Book& lhs, const Book& rhs) const
		{
			return lhs.quantityOnHand < rhs.quantityOnHand;
		}
	};

	LessThan_Quantity funcObj;
	sortedBooks.Sort(funcObj);

	ListBookInfo(sortedBooks);
}

void BookDatabase::ListSortedBookArrayByDate()
{
	// Make a copy of the book array
	Array<Book> sortedBooks = GetBookArray();

	struct LessThan_Date
	{
		bool operator () (const Book& lhs, const Book& rhs) const
		{
			return lhs.dateAdded > rhs.dateAdded;
		}
	};

	LessThan_Date funcObj;
	sortedBooks.Sort(funcObj);

	ListBookInfo(sortedBooks);
}
