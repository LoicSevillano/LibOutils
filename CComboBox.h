#pragma once
#include <string>
using namespace std;
#include "CControl.h"
class CComboBox :
    public CControl
{
public:
    void AddString(wstring sZ);
};

