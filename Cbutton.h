#pragma once

#include "CControl.h"
class Cbutton :
    public CControl
{
public:
    void Enable(bool bState);
    void Create(HINSTANCE hInst, long style,HWND hParent, int left, int top, int width, int height);
};

