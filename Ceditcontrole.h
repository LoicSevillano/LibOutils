#pragma once
#include <string>
#include "Ccontrole.h"

using namespace std;

class Ceditcontrole :
    public Ccontrole
{
public:
    wstring gettext();
    void settext(wstring sz);
};

