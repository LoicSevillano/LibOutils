#pragma once
#include <map>
#include <vector>
#include <memory>
using namespace std;
#include "CompatibilityVariant.h"
class CDataBaseRecordSet
{
private:
	map<wstring, vector<shared_ptr<CCompatibilityVariant>>> m_Record_Table;
	int m_Current_Position;
public:
	CDataBaseRecordSet();
	~CDataBaseRecordSet();
	CCompatibilityVariant GetCurrentFieldValue(wstring szName);
	CCompatibilityVariant GetFieldValue(wstring szField, int iRecord);

	CCompatibilityVariant GetCurrentFieldValue(int i);
	wstring GetFieldName(int i);

	void MoveNext();
	void MoveFirst();
	bool IsEOF();
	int FieldCount();
	map<wstring, vector<shared_ptr<CCompatibilityVariant>>> * GetRecordTable();
	void SetRecordFieldValue(wstring szField, vector<shared_ptr<CCompatibilityVariant>> Column);
};

