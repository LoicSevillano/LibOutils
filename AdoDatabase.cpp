#include <Windows.h>
#include <comutil.h>
#include <string>
#include "AdoDatabase.h"
#include "Tools.h"
#include "DataBaseRecordSet.h"

using namespace std;

BOOL CAdoDatabase::OpenDatabase(wstring Name)
{
	CoInitialize(NULL);

	m_pConnection.CreateInstance(__uuidof(Connection));
	pStream.CreateInstance(__uuidof(Stream));

	
	_bstr_t name = Name.data();

	m_type_provider = 0;
	//m_pConnection->ConnectionString =Name.GetBuffer();


	HRESULT hr = m_pConnection->Open( name, "", "", -1 );
	_StreamPtr  pStm(__uuidof(Stream));
	pStream = pStm;
	return (TRUE);
}

CTable* CAdoDatabase::OpenRecordset(wstring Name)
{
	std::list<CTable *>::iterator it;
	for (it = pListTable.begin(); it != pListTable.end();it++)
	{
		CTable *pTable = *it;
		if(!CTools::CompareNoCase(pTable->Name,Name))
		{
			return (pTable);
		}
	}
	CTable *pTable = new(CTable);
	spRSchema=m_pConnection->OpenSchema(adSchemaTables);
	while(!(spRSchema->adoEOF))
	{
        _bstr_t table_name = spRSchema->Fields->GetItem("TABLE_NAME")->Value;

		wstring szTable = table_name;
		if (!CTools::CompareNoCase(szTable,Name))
		{
				pTable->m_pRecordset.CreateInstance(__uuidof(Recordset));

				switch (m_type_provider)
				{
					case 0:
					pTable->m_pRecordset->CursorLocation = adUseClient;
					pTable->m_pRecordset->Open("select * from ["+table_name +"]" ,m_pConnection.GetInterfacePtr(), adOpenStatic,
					adLockReadOnly,-1);
					break;
					case 1 :
					pTable->m_pRecordset->PutRefActiveConnection( m_pConnection );
					pTable->m_pRecordset->CursorLocation = adUseClient;
					pTable->m_pRecordset->Open("select * from ["+table_name +"]",  vtMissing, adOpenStatic,
					adLockOptimistic, -1);
					break;
				}

				pTable->Name=Name;
				pTable->pParent=this;
				pListTable.push_back(pTable);
				return (pTable);
		}
		spRSchema->MoveNext();
	}
	return(FALSE);
}
CTable* CAdoDatabase::OpenRecordset(wstring Name, wstring FieldsToSelect)
{
	std::list<CTable *>::iterator it;
	variant_t v;
	v.vt = VT_BSTR;
	for (it = pListTable.begin(); it != pListTable.end(); it++)
	{
		CTable *pTable = *it;
		if(!CTools::CompareNoCase(pTable->Name,Name))
		{
			return (pTable);
		}
	}
	CTable *pTable = new(CTable);

	spRSchema=m_pConnection->OpenSchema(adSchemaTables);
	while(!(spRSchema->adoEOF))
	{
        _bstr_t table_name = spRSchema->Fields->GetItem("TABLE_NAME")->Value;
		wstring szTable=table_name;
		if (!CTools::CompareNoCase(szTable,Name))
		{
			wstring sZFiltre = L"select ";
				sZFiltre+=FieldsToSelect;
				sZFiltre+=L" from [";
				wstring sZTab;
				sZTab=table_name.GetBSTR();
				sZFiltre= sZFiltre+sZTab;
				sZFiltre+=L"]";
				pTable->m_pRecordset.CreateInstance(__uuidof(Recordset));
				switch (m_type_provider)
				{
					case 0:
					pTable->m_pRecordset->CursorLocation = adUseClient;
					v = sZFiltre.data();
					pTable->m_pRecordset->Open(v ,m_pConnection.GetInterfacePtr(), adOpenStatic,
					adLockOptimistic,-1);
					break;
					case 1 :
					pTable->m_pRecordset->PutRefActiveConnection( m_pConnection );
					pTable->m_pRecordset->CursorLocation = adUseClient;
					v = sZFiltre.data();
					pTable->m_pRecordset->Open(v,  vtMissing, adOpenStatic,
					adLockOptimistic, -1);
					break;
				}

				pTable->Name=Name;
				pTable->pParent=this;
				pListTable.push_back(pTable);
				return (pTable);
		}
		spRSchema->MoveNext();
	}
	return(FALSE);
}
int CAdoDatabase::GetTableCount()
{
	spRSchema=m_pConnection->OpenSchema(adSchemaTables);
	int n=0;
	while(!(spRSchema->adoEOF))
	{
		n++;
		spRSchema->MoveNext();
	}
	return (n);
}

CTable* CAdoDatabase::OpenRecordset(wstring Name, wstring FieldsToSelect, wstring Filter, int CursorLocation)
{
	std::list<CTable *>::iterator it;
	variant_t v;
	for (it = pListTable.begin(); it != pListTable.end(); it++)
	{
		CTable *pTable = *it;
		if(!CTools::CompareNoCase(pTable->Name,Name))
		{
			return (pTable);
		}
	}
	CTable *pTable = new(CTable);

	spRSchema=m_pConnection->OpenSchema(adSchemaTables);
	while(!(spRSchema->adoEOF))
	{
        _bstr_t table_name = spRSchema->Fields->GetItem("TABLE_NAME")->Value;
		
		wstring szTable = table_name;
		if (!CTools::CompareNoCase(szTable,Name))
		{
			wstring sZFiltre = L"select ";
				sZFiltre+=FieldsToSelect;
				sZFiltre+=L" from [";
				wstring sZTab;
				sZTab=table_name.GetBSTR();
				sZFiltre= sZFiltre+sZTab;
				sZFiltre+=L"]";
				pTable->m_pRecordset.CreateInstance(__uuidof(Recordset));
				pTable->Filter( Filter);
				switch (m_type_provider)
				{
					case 0:
					{
						switch(CursorLocation)
						{
						case 0 :
						pTable->m_pRecordset->CursorLocation = adUseClient;
						break;
						case 1 :
						pTable->m_pRecordset->CursorLocation = adUseServer;
						break;
						}
						v = sZFiltre.data();
						pTable->m_pRecordset->Open(v  ,m_pConnection.GetInterfacePtr(), adOpenStatic,
						adLockOptimistic,adCmdText);
						break;
					}
					case 1 :
					{
						pTable->m_pRecordset->PutRefActiveConnection( m_pConnection );
						switch(CursorLocation)
						{
							case 0 :
							pTable->m_pRecordset->CursorLocation = adUseClient;
							break;
							case 1 :
							pTable->m_pRecordset->CursorLocation = adUseServer;
							break;
						}
						v = sZFiltre.data();
						pTable->m_pRecordset->Open(v ,m_pConnection.GetInterfacePtr(), adOpenStatic,
						adLockOptimistic,-1);
						break;
					}

				}

				pTable->Name=Name;
				pTable->pParent=this;
				pListTable.push_back(pTable);
				return (pTable);
		}
		spRSchema->MoveNext();
	}
	return(FALSE);
}

CTable* CAdoDatabase::OpenRecordSetOnQuery(wstring SQLQuery, int CursorLocation)
{
	  

	CTable * pTable = new(CTable);

	VARIANT  *RecordsAffected=NULL;
	   pTable->m_pRecordset =   this->m_pConnection->Execute(SQLQuery.data(),RecordsAffected,1);


	pTable->Name=L"Query";
	pTable->pParent=this;
	return (pTable);


}

wstring CAdoDatabase::GetTableName(int n)
{
	if (n >=GetTableCount()) return L"";
	spRSchema->MoveFirst();
	for (int i=0;i<n;i++) spRSchema->MoveNext();
    _bstr_t table_name = spRSchema->Fields->GetItem("TABLE_NAME")->Value;

	wstring szTableName = table_name;
	return(szTableName);

}
long CTable::GetRecordCount()
{
	return (long)	m_pRecordset->RecordCount;
}
void CTable::MoveFirst()
{
	m_pRecordset->MoveFirst();
}
void CTable::MoveLast()
{
	m_pRecordset->MoveLast();
}
void CTable::MoveNext()
{
	m_pRecordset->MoveNext();
}
void CTable::Filter(wstring Filtre)
{
	variant_t v(Filtre.data());
	m_pRecordset->Filter=v;
}
variant_t CTable::GetFieldValue(int n)
{
	_variant_t Index;
	Index.iVal = n;
	Index.vt = VT_I2;
	return m_pRecordset->Fields->GetItem(Index)->Value;
}

wstring CTable::GetStringFieldValue(int n)
{
	VARIANT v;
	v = GetFieldValue(n);
	if (v.vt==VT_NULL)
		return L"";
	else
	{
		wstring sZ = v.bstrVal;
		return sZ;
	}

}
wstring CTable::GetStringFieldValue(wstring s)
{
	VARIANT v;
	v = GetFieldValue(s);
	if (v.vt==VT_NULL)
		return L"";
	else
	{
		wstring sZ = v.bstrVal;
		return sZ;
	}

}
int CTable::GetIntFieldValue(int n)
{
	VARIANT v;
	v = GetFieldValue(n);
	return v.iVal;

}

int CTable::GetIntFieldValue(wstring s)
{
	VARIANT v;
	v = GetFieldValue(s);
	if (v.vt==VT_NULL)
		return 0;
	else
	{
		return v.iVal;
	}

}
CURRENCY CTable::GetCurrencyFieldValue(int n)
{
	VARIANT v;
	v = GetFieldValue(n);
	return v.cyVal;
}

void CTable::Sort(wstring szSort)
{
	wchar_t cSort[256];
	wcscpy_s(cSort,256,szSort.data());
	m_pRecordset->Sort = cSort;
}

DATE CTable::GetDateFieldValue(int n)
{
	VARIANT v;
	v = GetFieldValue(n);
	return v.date;
}
double CTable::GetDoubleFieldValue(int n)
{
	VARIANT v;
	v = GetFieldValue(n);
	return v.dblVal;
}
double CTable::GetDoubleFieldValue(wstring s)
{
	VARIANT v;
	v = GetFieldValue(s);
	if (v.vt==VT_NULL)
		return 0;
	else
	{
		return v.dblVal;
	}

}

void CTable::Move(long n)
{


	if (n==0)
	{
		MoveFirst();
	}
	else
	{
		MoveFirst();
		for (int i=0;i<n;i++) MoveNext();
	}
}

void CTable::Update()
{
	m_pRecordset->Update();
}

void CTable::SetFieldValue(int n,variant_t v)
{
	_variant_t Index;
	Index.iVal = n;
	Index.vt = VT_I2;
	m_pRecordset->Fields->GetItem(Index)->Value=v;
}

void CTable::AddNew()
{
	m_pRecordset->AddNew();
}

variant_t CTable::GetFieldValue(wstring s)
{
	variant_t vnull;
	vnull.vt=VT_NULL;
	if(GetFieldNumber(s)==-1) return vnull;
	variant_t vres = m_pRecordset->GetCollect(s.data());

	return(vres);
}

void CTable::SetFieldValue(wstring s, variant_t v)
{
	variant_t vv(s.data());
	if (vv.vt == VT_ERROR)
	{
		MessageBoxW(NULL, s.data(),L"Erreur",MB_OK);
	}
	m_pRecordset->Fields->GetItem(vv)->Value=v;	
}

int CTable::GetFieldType(wstring s)
{
	variant_t vv=s.data();
	variant_t vres = m_pRecordset->GetCollect(s.data());
	return(vres.vt);
}

int CTable::GetFieldType(int i)
{
	variant_t vres = m_pRecordset->GetCollect(i);
	return(vres.vt);
}

void CTable::Close()
{
	m_pRecordset->Close();
	std::list<CTable *>::iterator it;
	for (it = pParent->pListTable.begin(); it != pParent->pListTable.end(); it++)
	{
		if (*it == this)
		{
			pParent->pListTable.erase(it);
			break;
		}
	}

	delete this;

}

wstring CTable::GetFieldName(int n)
{
	if (n < m_pRecordset->Fields->Count)
	{
		_variant_t Index;
		Index.iVal = n;
		Index.vt = VT_I2;
		wstring s = m_pRecordset->Fields->GetItem(Index)->GetName();
//		s.Format(L"%s",spRS->Fields->GetItem(Index)->GetName());
		return s;

	}
	return L"";
}

int CTable::GetFieldNumber(wstring s)
{
	for (int i=0;i<m_pRecordset->Fields->Count;i++)
	{
		if (GetFieldName(i) == s) return i;
	}
	return -1;
}

int CTable::GetFieldCount()
{
	return m_pRecordset->Fields->Count;
}







void CTable::MovePrev()
{
	m_pRecordset->MovePrevious();

}

void CAdoDatabase::CloseDatabase()
{
	m_pConnection->Close();
}


bool CTable::IsEOF()
{
	return  m_pRecordset->adoEOF !=0 ;
}

shared_ptr<CDataBaseRecordSet> CAdoDatabase::ExecuteSQL(wstring SQLQuery)
{
	#define VT_BOOL 11
	#define VT_I1 16
	#define VT_I2 2
	#define VT_I4 3
	#define VT_I8 20
	#define VT_DATE 7
	#define VT_R4 4
	#define VT_R8 5
	#define VT_BSTR 8
	#define VT_NULL 1


	CTable* pRecord = OpenRecordSetOnQuery(SQLQuery, 0);
	shared_ptr< CDataBaseRecordSet> pDataBaseRecordSet = make_shared< CDataBaseRecordSet>();
	map<wstring, int> MapOfFields;

/*	if (pRecord->GetFieldCount())
	{

		for (auto i = 0; i < pRecord->GetFieldCount(); i++)
		{
			auto pNode_Field = pNode_Fields->AddNode(L"Field");
			pNode_Field->AddAttribute(L"Id", pRecord->GetFieldName(i));
			pNode_Field->AddAttribute(L"Type", pRecord->GetFieldType(pRecord->GetFieldName(i)));
		}

		while (!pRecord->IsEOF())
		{
			auto iRec = 0;
			auto pNode_Record = pNode_Records->AddNode(L"Record");
			for (auto i = 0; i < pRecord->GetFieldCount(); i++)
			{
				wstring szFieldNumber = pRecord->GetFieldName(i);//CTools::Format(L"Field%d", i);
				int iType = pRecord->GetFieldType(pRecord->GetFieldName(i));
				switch (iType)
				{
				case VT_BSTR:
				case 202:

					pNode_Record->AddAttribute((wchar_t*)szFieldNumber.data(), pRecord->GetStringFieldValue(i).data());
					break;
				case VT_BOOL:
				case VT_I1:
				case VT_I2:
				case VT_I4:
				case VT_I8:
					pNode_Record->AddAttribute((wchar_t*)szFieldNumber.data(), pRecord->GetIntFieldValue(i));

					break;
				case VT_DATE:
					pNode_Record->AddAttribute((wchar_t*)szFieldNumber.data(), pRecord->GetDateFieldValue(i));

					break;
				case VT_R4:
				case VT_R8:
					pNode_Record->AddAttribute((wchar_t*)szFieldNumber.data(), pRecord->GetDoubleFieldValue(i));

					break;
				case VT_EMPTY:
				case VT_NULL:
					pNode_Record->AddAttribute((wchar_t*)szFieldNumber.data(), L"");
					break;
				default:
					break;
				}
			}

			pRecord->MoveNext();
		}
	}*/

	return NULL;
}
