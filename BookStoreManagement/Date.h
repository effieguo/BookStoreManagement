#pragma once


class Date
{
	int month, day, year;

	bool operator < (const Date& rhs) const
	{
		if (year < rhs.year)
			return true;

		if (month < rhs.month)
			return true;

		if (day < rhs.day)
			return true;

		return false;
	}
};