#include "CListBox.h"
#include <string>
using namespace std;
void CListBox::AddString(std::wstring sz)
{
	SendMessage(m_hWnd, LB_ADDSTRING, 0, (LPARAM)sz.data());
}
int CListBox::GetCurSel()
{
	return  SendMessage(GethWnd(), LB_GETCURSEL, 0, 0);

}
wstring CListBox::GetText(int iCur)
{
	wchar_t Reponse[256];
	SendMessage(GethWnd(), LB_GETTEXT, iCur, (LPARAM)Reponse);
	return Reponse;
}

void CListBox::SetCursel(int iNum) 
{
	SendMessage(GethWnd(), LB_SETCURSEL, iNum, 0);
}

int CListBox::FindString(wstring szFind) {
	int iRet = SendMessage(GethWnd(), LB_FINDSTRINGEXACT, -1, (LPARAM)szFind.data());
	return iRet;
}

void CListBox::Create(HINSTANCE hInst, long style, HWND hParent, int left, int top, int width, int height)
{
	m_hWnd = CreateWindowEx(0, L"LISTBOX", L"", style, left, top, width, height, hParent, NULL, hInst, this);
}



