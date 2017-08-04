#ifndef HelpFuncs_H
#define HelpFuncs_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "BookDatabase.h"

using namespace std;

class HelpFuncs
{
public:

	static void DisplayTitle()
	{
		cout << "***************************************************" << endl;
		cout << right;
		cout << setw(30) << "Serendipity Booksellers" << setw(17) << endl;
	}

	static void DisplayDate()
	{
		time_t t = time(0);   // get time now
		tm now;
		localtime_s(&now, &t);
		cout << (now.tm_year + 1900) << '-'
			<< (now.tm_mon + 1) << '-'
			<< now.tm_mday
			<< endl;
	}

	static int GetMenuIndex()
	{
		char cmd[500];
		do
		{
			cin.getline(cmd, 500, '\n');
		} while (*(cmd + 1) != '\0');

		return atoi(cmd);
	}

};

#endif



