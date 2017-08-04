#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Array.h"
using namespace std;

struct Date
{
	int month, day, year;

public:
	Date()
	{

	}

	Date(int month, int day, int year)
	{
		this->month = month;
		this->day = day;
		this->year = year;
	}

	bool operator > (const Date& rhs) const;
	
};

class Book
{
public:
	long long ISBN;

	string	title;
	string	author;
	string	publisher;
	Date	dateAdded;

	int		quantityOnHand;
	float	wholeSaleCost;
	float	retailPrice;

public:
	Book()
	{

	}

	bool operator == (const Book& rhs);

	enum ListKey
	{
		WholeSaleValue = 1,
		RetailValue = 1 << 1,
		All = ~0
	};
	
	void PrintBookInfo(ListKey key = All) const;

	friend class BookDatabase;

	friend ifstream& operator>>(ifstream& in, Book&b);
};

