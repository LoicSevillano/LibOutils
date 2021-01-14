#include "Cfenetres.h"


HWND Cfenetres::getwnd()
{
	return m_hWnd;
}

void Cfenetres::setwnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

