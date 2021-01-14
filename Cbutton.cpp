#include "Cbutton.h"
#include <Windowsx.h>
void Cbutton::Enable(bool bState)
{
	Button_Enable(m_hWnd, bState);
}
void Cbutton::Create(HINSTANCE hInst, long style, HWND hParent, int left, int top, int width, int height)
{
	m_hWnd = CreateWindowEx(0, L"Button", L"", style, left, top, width, height, hParent, NULL, hInst, this);
}
