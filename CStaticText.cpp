#include "CStaticText.h"


void CStaticText::Create(HINSTANCE hInst, long style, HWND hParent, int left, int top, int width, int height)
{
	m_hWnd = CreateWindowEx(0, L"Static", L"", style, left, top, width, height, hParent, NULL, hInst, this);
}

void CStaticText::SetText(wstring text)
{
	SendMessage(GethWnd(), WM_SETTEXT, NULL, (LPARAM)text.data());
}
