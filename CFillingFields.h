#pragma once
#include "CDialog.h"
#include ".\..\LibOutils\CListBox.h"
#include "CEditBox.h"
#include ".\..\LibOutils\AdoDatabase.h"


class CFillingFields
{public:

	void fillingFields(CListBox m_List,wstring databaseField, CListBox editName);
};

