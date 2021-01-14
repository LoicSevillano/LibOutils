#pragma once
#include <string>
using namespace std;
class CTimeUtils
{
public:
	CTimeUtils();
	~CTimeUtils();
	static wstring TimetToString(time_t t);
	static time_t YearMonthDayToTime(int Day, int Month, int Year);
	static bool IsBisextil(int Year);
	static int GetYear(time_t t);
};

