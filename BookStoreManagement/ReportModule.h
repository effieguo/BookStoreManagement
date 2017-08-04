#ifndef ReportModule_H
#define ReportModule_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Array.h"
#include "Book.h"
#include "BookDatabase.h"
#include "HelpFuncs.h"
#include "Module.h"
using namespace std;


/*The Report module will analyze the information in the Inventory Database to produce any of the following reports: 
 
• Inventory List. A list of information on all books in the inventory. 
 
• Inventory Wholesale Value. A list of the wholesale value of all books in the inventory and the total wholesale value of the inventory. 
 
• Inventory Retail Value. A list of the retail value of all books in the inventory and the total retail value of the inventory. 
 
• List by Quantity. A list of all books in the inventory sorted by quantity on hand.  The books with the greatest quantity on hand will be listed first. 
 
• List by Cost. A list of all books in the inventory, sorted by wholesale cost. The books with the greatest wholesale cost will be listed first. 
 
• List by Age. A list of all books in the inventory, sorted by purchase date. The books that have been in the inventory longest will be listed first. */


class ReportModule : public Module
{
private:
	BookDatabase& bookDatabase;

public:
	ReportModule(BookDatabase& db)        //constructor
		: bookDatabase(db)
	{
	}

	void Run() override;
	

private:
	void ListInventory();


	void ListWholeSaleValue();


	void ListRetailValue();
	

	void ListSortedByWholeSaleCost();


	void ListSortedByQuantity();

	void ListSortedByDate();

};
#endif
