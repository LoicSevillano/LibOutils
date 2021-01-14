#include "CompatibilityVariant.h"
#include <wchar.h>

#if defined WIN32 || defined WINDOWS_API
#pragma warning(disable:4996)
#endif

CCompatibilityVariant::CCompatibilityVariant()
{
    llVal = NULL;
    bstrVal = NULL;
    iVal = -1;
    dblVal = 0.0;
    wstringVal = L"";
    dateVal = 0;
    boolVal = false;
};

CCompatibilityVariant::CCompatibilityVariant(wchar_t * Text)
{
    llVal = NULL;
    bstrVal = (Text);
    iVal = -1;
    llVal = NULL;
    dblVal = 0.0;
    wstringVal = L"";
    dateVal = 0;
    boolVal = false;

};

CCompatibilityVariant::CCompatibilityVariant(const wchar_t * Text)
{
    llVal = NULL;
    bstrVal = (wchar_t *) Text;
    iVal = -1;
    llVal = NULL;
    dblVal = 0.0;
    wstringVal = L"";
    dateVal = 0;
    boolVal = false;

};

CCompatibilityVariant::CCompatibilityVariant(void* l)
{
    iVal = -1;
    bstrVal = NULL;
    llVal = l;
    dblVal = 0.0;
    wstringVal = L"";
    dateVal = 0;
    boolVal = false;

}
CCompatibilityVariant::CCompatibilityVariant(wstring s)
{
    iVal = -1;
    bstrVal = NULL;
    llVal = 0;
    dblVal = 0.0;
    wstringVal =s;
    dateVal = 0;
    boolVal = false;

}

CCompatibilityVariant::CCompatibilityVariant(time_t t)
{
    iVal = -1;
    bstrVal = NULL;
    llVal = 0;
    dblVal = 0.0;
    wstringVal = L"";
    dateVal = t;
    boolVal = false;

}

CCompatibilityVariant::CCompatibilityVariant(bool b)
{
    iVal = -1;
    bstrVal = NULL;
    llVal = 0;
    dblVal = 0.0;
    wstringVal = L"";
    dateVal = 0;
    boolVal = b;

}

CCompatibilityVariant::~CCompatibilityVariant()
{
}

CCompatibilityVariant CCompatibilityVariant::SetVariantFromwString(wstring  s)
{
    CCompatibilityVariant vt;
    vt.wstringVal = s;
    vt.iVal = -1;
    vt.llVal = NULL;
    vt.dblVal = 0.0;
    vt.boolVal = false;
    return (vt);
}

CCompatibilityVariant CCompatibilityVariant::SetVariantFromwDate(time_t  t)
{
    CCompatibilityVariant vt(t);

    return (vt);
}

CCompatibilityVariant CCompatibilityVariant::SetVariantFromText(wchar_t * Text)
{
    CCompatibilityVariant vt;
    vt.bstrVal = Text;
    vt.iVal = -1;
    vt.llVal = NULL;
    vt.dblVal = 0.0;
    vt.boolVal = false;
    vt.wstringVal = L"";
    return (vt);
}

CCompatibilityVariant CCompatibilityVariant::SetVariantFromText(const wchar_t * Text)
{
    CCompatibilityVariant vt;
    vt.bstrVal = (wchar_t *) Text;
    vt.iVal = -1;
    vt.llVal = NULL;
    vt.dblVal = 0.0;
    vt.boolVal = false;
    vt.wstringVal = L"";
    return (vt);
}

CCompatibilityVariant CCompatibilityVariant::SetVariantFromvoid(void* l)
{
    CCompatibilityVariant vt;
    vt.iVal = -1;
    vt.bstrVal = NULL;
    vt.llVal = l;
    vt.boolVal = vt.llVal != 0;
    vt.wstringVal = L"";
    return (vt);
}

CCompatibilityVariant CCompatibilityVariant::SetVariantFromdouble(double x)
{
    CCompatibilityVariant vt;
    vt.iVal = -1;
    vt.bstrVal = NULL;
    vt.llVal = NULL;
    vt.dblVal = x;
    vt.wstringVal = L"";
    vt.boolVal = false;
    return (vt);
}

CCompatibilityVariant CCompatibilityVariant::SetVariantFromBool(bool b)
{
    CCompatibilityVariant vt;
    vt.iVal = -1;
    vt.bstrVal = NULL;
    vt.llVal = NULL;
    vt.dblVal = 0;
    vt.boolVal = b;
    vt.wstringVal = L"";
    return (vt);
}
