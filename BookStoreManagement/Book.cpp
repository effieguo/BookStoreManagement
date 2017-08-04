#define _CRT_SECURE_NO_WARNINGS

#include "Book.h"

bool Date::operator > (const Date& rhs) const
{
	if (year > rhs.year)
		return true;

	if (year == rhs.year && month > rhs.month)
		return true;

	if (year == rhs.year && month == rhs.month && day > rhs.day)
		return true;

	return false;
}

bool Book::operator == (const Book& rhs)
{
	return this->title == rhs.title;
}


void Book::PrintBookInfo(ListKey key/* = All*/) const
{
	cout << right
		<< setw(18) << "ISBN: " << this->ISBN << endl
		<< setw(18) << "Title: " << this->title << endl
		<< setw(18) << "Author: " << this->author << endl
		<< setw(18) << "Publisher: " << this->publisher << endl
		<< setw(18) << "Date Added: " << this->dateAdded.month << "/" << this->dateAdded.day << "/" << this->dateAdded.year << endl
		<< setw(18) << "Quantity-On-Hand: " << this->quantityOnHand << endl;

	if (key & ListKey::WholeSaleValue)
		cout << setw(18) << "Wholesale Cost: " << this->wholeSaleCost << endl;

	if (key & ListKey::RetailValue)
		cout << setw(18) << "Retail Price: " << this->retailPrice << endl;
}


static void ReadStringBetweenQuotes(ifstream& inFile, string& str)
{
	inFile.ignore(2);

	while (true)
	{
		char readBuf;
		inFile >> std::noskipws >> readBuf;
		str += readBuf;

		if (inFile.peek() == '\"')
			break;
	}

	inFile.ignore(1);
}

ifstream& operator >> (ifstream& inFile, Book& book)
{
	// Read ISBN
	inFile >> book.ISBN;

	// This is necessary to read in the white spaces in 
	ReadStringBetweenQuotes(inFile, book.title);
	ReadStringBetweenQuotes(inFile, book.author);
	ReadStringBetweenQuotes(inFile, book.publisher);

	inFile >> std::skipws
		>> book.dateAdded.month
		>> book.dateAdded.day
		>> book.dateAdded.year
		>> book.wholeSaleCost
		>> book.retailPrice
		>> book.quantityOnHand;

	return inFile;
}