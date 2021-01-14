#include "TimeUtils.h"
#include "Tools.h"


CTimeUtils::CTimeUtils()
{
}


CTimeUtils::~CTimeUtils()
{
}

#include <windows.h>
#include <time.h>

wstring CTimeUtils::TimetToString(time_t t)
{
	if (!t) return L"";
	int MonthDays[] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
	int Year = t / 365.25;
	int NumberOfDays = t - 365.25 * Year;
	Year += 1900;
	bool bBisextil = IsBisextil(Year);
	if (bBisextil) for (auto i = 1; i < 12; i++) MonthDays[i]++;
	int iMonth = 0;
	while (MonthDays[iMonth] < NumberOfDays) iMonth = (iMonth + 1) % 12;
	int iDay = NumberOfDays - MonthDays[iMonth - 1];
	iMonth++;

	wstring szNom = CTools::Format(L"%02d/%02d/%4d", iDay, iMonth, Year);
	return szNom;

}
time_t CTimeUtils::YearMonthDayToTime(int Day, int Month, int Year)
{
	int MonthDays[] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
	bool bBisextil = IsBisextil(Year);
	if (bBisextil) for (auto i = 1; i < 12; i++) MonthDays[i]++;
	Year -= 1900;
	int NumberOfDays = Day;
	if (Month > 1)
		NumberOfDays += MonthDays[Month - 2];
	return Year * 365.25 + NumberOfDays;

}
bool CTimeUtils::IsBisextil(int Year)
{
	bool bBisextil = false;
	if (Year % 4 == 0)
	{
		bBisextil = true;
	}
	else if (Year % 100 == 0)
	{
		if (Year % 400 == 0)
			bBisextil = true;
		else
			bBisextil = false;
	}
	else
	{
		bBisextil = false;
	}
	return bBisextil;
};
int CTimeUtils::GetYear(time_t t)
{
	int Year = t / 365.25;
	Year += 1900;
	return Year;
}