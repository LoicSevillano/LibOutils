#include "CComboBox.h"
void CComboBox::AddString(wstring sZ)
{
	SendMessage(this->GethWnd(), CB_ADDSTRING, 0, (LPARAM)sZ.data());
}