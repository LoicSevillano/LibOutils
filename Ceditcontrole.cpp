#include "Ceditcontrole.h"
#include <Windows.h>
#include "Ccontrole.h"

wstring Ceditcontrole::gettext()
{
	
	wchar_t buffer[128];
	SendMessage(getwnd(), WM_GETTEXT, 0, (LPARAM)buffer);
	return wstring (buffer);
}

void Ceditcontrole::settext(wstring sz)
{
	SendMessage(getwnd(), WM_SETTEXT, 0, (LPARAM)sz.data());

}
