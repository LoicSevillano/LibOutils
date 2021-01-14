#pragma once
#include <stdarg.h>
#include <string>
#include "TimeUtils.h"
using namespace std;
class CTools
{
public:
    static bool CompareNoCase(std::wstring pwBuf1, std::wstring pwBuf2)

    {
        if (pwBuf1.length() != pwBuf2.length()) return true;
        for (int i = 0; i < (int)pwBuf1.length(); i++)
        {
            if (toupper(pwBuf1[i]) != toupper(pwBuf2[i])) return true;
        }
        return false;
    }
    static bool CompareNoCase(std::wstring pwBuf1, wchar_t* pwwBuf2)
    {
        std::wstring pwBuf2 = pwwBuf2;
        if (pwBuf1.length() != pwBuf2.length()) return true;
        for (int i = 0; i < (int)pwBuf1.length(); i++)
        {
            if (toupper(pwBuf1[i]) != toupper(pwBuf2[i])) return true;
        }
        return false;
    }

    static wstring Format(wstring szFormat, ...)
    {
        va_list arglist;
        wchar_t szBuf[1024];

        va_start(arglist, szFormat);
        _vsnwprintf_s(szBuf, 1024, szFormat.data(), arglist);
        va_end(arglist);
        wstring szResult = szBuf;

        return szResult;
    }

    static wstring Format(wchar_t *szFormat, ...)
    {
        va_list arglist;
        wchar_t szBuf[1024];

        va_start(arglist, szFormat);
        _vsnwprintf_s(szBuf, 1024, szFormat, arglist);
        va_end(arglist);
        wstring szResult = szBuf;

        return szResult;
    }
    static bool IsNumeric(wstring Text)
    {
        size_t iCar;
        wchar_t CarToChecK;
        bool  bExponent = false;
        bool  bChangeSignExponent = false;
        bool  bDecimalPoint = false;
        bool  bReturn = true;

        for (iCar = 0; iCar < Text.length(); iCar++)
        {
            CarToChecK = Text[iCar];
            if (iCar == 0)
            {
                switch (CarToChecK)
                {
                case '.':
                    bDecimalPoint = true;
                    break;
                case '-':
                    break;
                case '+':
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    break;
                default:
                    bReturn = false;
                    break;
                }
            }

            else if (iCar == Text.length() - 1)
            {
                switch (CarToChecK)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    break;
                case '.':
                    bDecimalPoint = true;
                    break;

                case 'e':
                case 'E':

                    if (!bExponent)
                    {
                        bExponent = true;
                        break;
                    }
                default:
                    bReturn = false;
                    break;
                }
            }
            else
            {
                switch (CarToChecK)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    break;
                case '.':
                    if (bDecimalPoint)
                    {
                        bReturn = false;
                        break;
                    }
                    bDecimalPoint = true;
                    break;
                case '-':
                case '+':
                    if (Text[iCar - 1] == 'E' || Text[iCar - 1] == 'e')
                    {
                        if (!bChangeSignExponent)
                        {
                            bChangeSignExponent = true;
                            break;
                        }
                    }
                    bReturn = false;
                    break;
                case 'e':
                case 'E':
                    if (!bExponent)
                    {
                        bExponent = true;
                        break;
                    }
                    bReturn = false;
                    break;
                default:
                    bReturn = false;
                }
            }
            if (!bReturn) break;
        }

        return bReturn;
    }
    static bool IsNumericPhone(wstring Text)
    {
        return IsNumericWithFixedDigits(Text, 10);
    }

    static bool IsNumericCodePostal(wstring Text)
    {
        return IsNumericWithFixedDigits(Text, 5);
    }
    static bool IsNumericWithFixedDigits(wstring Text,int nDigits)
    {
        if (Text.length() != nDigits)return false;
        size_t iCar;
        wchar_t CarToChecK;
        bool  bReturn = true;

        for (iCar = 0; iCar < Text.length(); iCar++)
        {
            CarToChecK = Text[iCar];

            switch (CarToChecK)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                break;
            default:
                bReturn = false;
                break;
            }
        }
        return true;
    }

    static bool IsDate(wstring Text)
    {
        if (Text.empty()) return true;
        if (Text.length() != 10)return false;
        if (Text[2] != '/' || Text[5] != '/') return false;

        auto szDay = Text.substr(0, 2);
        auto szMonth = Text.substr(3, 2);
        auto szYear = Text.substr(6, 4);

        if(IsNumericWithFixedDigits(szDay, 2) == false) return false;
        if (IsNumericWithFixedDigits(szMonth, 2) == false) return false;
        if (IsNumericWithFixedDigits(szYear, 4) == false) return false;

        auto iDay = _wtoi(szDay.data());
        auto iMonth = _wtoi(szMonth.data());
        auto iYear = _wtoi(szYear.data());

        int iMaxDayMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        if (CTimeUtils::IsBisextil(iYear)) {
            iMaxDayMonth[1] = 29;
        }
        if (iMonth <= 0 || iMonth > 12) return false;

        if (iDay > iMaxDayMonth[iMonth-1] || iDay <= 0)return false;

        return true;
    }
    static wstring SQLTreatStringField(wstring szText)
    {
        int iSearch = 0;
        wstring szReturn;
        for (;;)
        {
            auto iFind = szText.substr(iSearch).find_first_of(L"'");
            if (iFind == string::npos)
            {
                szReturn += szText.substr(iSearch);
                break;
            }
            iFind += iSearch;
            szReturn += szText.substr(iSearch,iFind+1) + L"'";
            iSearch = iFind + 1;
            if (iSearch >= szText.length()) break;
        }
        return szReturn;
    }
};

