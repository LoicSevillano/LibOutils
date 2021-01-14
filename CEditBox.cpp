#include "CEditBox.h"
//  recupere le texte de l'edit box
wstring CEditBox::GetText()
{
	wchar_t Reponse[256];
	SendMessage(GethWnd(), WM_GETTEXT, 256, (LPARAM) Reponse);
	return Reponse;
}
//  envoie le texte à l'edit box
void CEditBox::SetText(wstring sz)
{
	SendMessage(GethWnd(), WM_SETTEXT, 0, (LPARAM)sz.data());
}

void CEditBox::Create(HINSTANCE hInst, long style, HWND hParent, int left, int top, int width, int height)
{
	m_hWnd = CreateWindowEx(0, L"Edit", L"", style, left, top, width, height, hParent, NULL, hInst, this);
}



