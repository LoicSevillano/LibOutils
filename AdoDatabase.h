#pragma once
#include <list>
#include <string>
#include <memory>
//#include <Windows.h>
#include <comutil.h>
using namespace std;

#import"C:\Program Files (x86)\Common Files\System\ado\msado15.dll" no_namespace rename ("EOF", "adoEOF")

class CDataBaseRecordSet;
class CAdoDatabase;
class CTable
{
public:
	void MovePrev();
	int GetIntFieldValue(wstring s);
	double GetDoubleFieldValue(wstring s);
	int GetFieldCount();
	int GetFieldNumber(wstring s);
	wstring GetFieldName(int i);
	void Close();
	int GetFieldType(wstring s);
	int GetFieldType(int i);

	void SetFieldValue(wstring s, variant_t v);
	variant_t GetFieldValue(wstring s);
	void AddNew();
	void SetFieldValue(int n,variant_t v);
	void Update();
	DATE GetDateFieldValue(int n);
	void Sort(wstring szSort);
	CURRENCY GetCurrencyFieldValue(int n);
	int GetIntFieldValue(int n);
	double GetDoubleFieldValue(int n);
	wstring GetStringFieldValue(int n);
	wstring GetStringFieldValue(wstring s);
	wstring Name;
	_RecordsetPtr m_pRecordset;
	void MoveFirst();
	void MoveLast();
	void MoveNext();
	void Move (long n);
	long GetRecordCount();
	void Filter(wstring Filtre);
	variant_t GetFieldValue(int n);
	CAdoDatabase *pParent;

	bool IsEOF();
};
class CAdoDatabase
{
	public :
		void CloseDatabase();
		CAdoDatabase()
		{

		}
		wstring GetTableName(int n);
		int GetTableCount();
	_ConnectionPtr m_pConnection;
	_RecordsetPtr spRSchema;
	_StreamPtr pStream;

	std::list<CTable *> pListTable;
	BOOL OpenDatabase(wstring Name);
	CTable* OpenRecordset(wstring Name);
	CTable* OpenRecordset(wstring Name, wstring FieldsToSelect);
	CTable* OpenRecordset(wstring Name, wstring FieldsToSelect, wstring Filter, int CursorLocation = 1);
	CTable* OpenRecordSetOnQuery(wstring SQLQuery, int CursorLocation);
	shared_ptr<CDataBaseRecordSet> ExecuteSQL(wstring SQLQuery);
	int m_type_provider;
};