#pragma once
#include "CControl.h"
#include <string>

using namespace std;
class CListBox :
    public CControl
{
public:
    //
    void AddString(std::wstring sz);
    int GetCurSel();
    void SetCursel(int iNum);
    wstring GetText(int iCur);
    int FindString(wstring szFind);

    void Create(HINSTANCE hInst, long style, HWND hParent, int left, int top, int width, int height);
};

