#ifndef BookDatabase_H
#define BookDatabase_H

#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Array.h"
#include "Book.h"
using namespace std;


class BookDatabase
{
protected:
	Array<Book> books;  //contain array of books

public:
	void Init(const char*);

	Array<Book> GetBookArray();

	const Array<Book>& GetBookArray() const;

	void AddBook(const Book& book, const int quantity = 1); // book should be initialized, including the dateAdded member
	
	bool DeleteBook(const string& title, const int quantity = 1);

	bool DeleteBook(const long long ISBN, const int quantity = 1);

	
	struct EditValue
	{
		long long Longlong;
		int Integer;
		float Float;
		string String;
		Date _Date;
	};

	
	void EditBook(const string& title, const string& editItem, EditValue& val);
	
	void EditBook(const long long ISBN, const string& editItem, EditValue& val);

	Book* LookUpBook(const string& title);
	
	const Book* LookUpBook(const string& title) const;

	Book* LookUpBook(const long long ISBN);

	const Book* LookUpBook(const long long ISBN) const;

	void UpdateBookList(const char* fileName) const;

	void ListBookInfo(const Array<Book>& bookArray, const Book::ListKey key = Book::All);
	

	void ListSortedBookArrayByRetailPrice();
	

	void ListSortedBookArrayByWholeSaleCost();
	

	void ListSortedBookArrayByQuantity();
	

	void ListSortedBookArrayByDate();
};
#endif