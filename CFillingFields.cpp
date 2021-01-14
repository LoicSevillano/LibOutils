#include "CFillingFields.h"

//RESOLVE: Trouver l'erreur 

//Rempli les cases des editbox
void fillingFields(CTable *pRecord,wstring databaseField, CEditBox editName)
{
	auto sz = pRecord->GetStringFieldValue(databaseField);
	editName.SetText(sz);
}


