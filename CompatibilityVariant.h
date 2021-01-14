#pragma once

#ifndef COMPATIBILITVARIANT_H
#define COMPATIBILITVARIANT_H

#if defined WIN32 || defined WINDOWS_API
#pragma warning(disable:4996)
#else
#include <time.h>
#endif


#include <string>
using namespace std;

class CCompatibilityVariant
{
public:
    CCompatibilityVariant();
    CCompatibilityVariant(wchar_t * Text);
    CCompatibilityVariant(const wchar_t * Text);
    CCompatibilityVariant(void* l);
    CCompatibilityVariant(time_t s);
    CCompatibilityVariant(wstring s);
    CCompatibilityVariant(bool b);

    ~CCompatibilityVariant();

    int      iVal;
    void*    llVal;
    double	 dblVal;
    wchar_t * bstrVal;
    wstring wstringVal;
    time_t dateVal;
    bool boolVal;


public:
    static CCompatibilityVariant SetVariantFromText(wchar_t * Text);
    static CCompatibilityVariant SetVariantFromText(const wchar_t * Text);
    static CCompatibilityVariant SetVariantFromvoid(void* l);
    static CCompatibilityVariant SetVariantFromdouble(double x);
    static CCompatibilityVariant SetVariantFromwString(wstring  s);


    static CCompatibilityVariant SetVariantFromwDate(time_t  s);
    static CCompatibilityVariant SetVariantFromBool(bool  b);


    CCompatibilityVariant& operator=(const CCompatibilityVariant& var)
    {
        if (&var != this)
        {
            bstrVal    = var.bstrVal;
            llVal      = var.llVal;
            iVal       = var.iVal;
            dblVal     = var.dblVal;
            wstringVal = var.wstringVal;
            dateVal    = var.dateVal;
            boolVal    = var.boolVal;
        }
        return *this;
    }
};


struct pEnvironment
{
    wchar_t *              Name=NULL;
    CCompatibilityVariant  Value;
};


#endif