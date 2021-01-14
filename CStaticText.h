#pragma once
#include "CControl.h"
#include <string>

using namespace std;

class CStaticText :
    public CControl
{
public:
    void Create(HINSTANCE hInst, long style, HWND hParent, int left, int top, int width, int height);
    void SetText(wstring text);
};

