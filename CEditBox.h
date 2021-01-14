#pragma once
#include <string>
using namespace std;
#include "CControl.h"

class CEditBox :
    public CControl
{
public:
    //  recupere le texte de l'edit box
    wstring GetText();
    //  envoie le texte à l'edit box
    void SetText(wstring sz);

    void Create(HINSTANCE hInst, long style, HWND hParent, int left, int top, int width, int height);

};

