#include "DataBaseRecordSet.h"


CDataBaseRecordSet::CDataBaseRecordSet()
{
	m_Current_Position = 0;
}


CDataBaseRecordSet::~CDataBaseRecordSet()
{
}
map<wstring, vector<shared_ptr<CCompatibilityVariant>>> * CDataBaseRecordSet::GetRecordTable()
{
	return &m_Record_Table;
}

CCompatibilityVariant CDataBaseRecordSet::GetCurrentFieldValue(wstring szName)
{
	return GetFieldValue(szName, m_Current_Position);
}

CCompatibilityVariant CDataBaseRecordSet::GetCurrentFieldValue(int i)
{
	auto it = next(m_Record_Table.begin(), i)->second;
	return *it[m_Current_Position];
}

CCompatibilityVariant CDataBaseRecordSet::GetFieldValue(wstring szField,int iRecord)
{
	auto pColumn = (*GetRecordTable())[szField];
	auto wReturn = pColumn[iRecord];
	return *wReturn;
}

wstring CDataBaseRecordSet::GetFieldName(int i)
{
	auto it = next(m_Record_Table.begin(), i)->first;
	return it;
}

void CDataBaseRecordSet::MoveNext()
{
	m_Current_Position++;
}

void CDataBaseRecordSet::MoveFirst()
{
	m_Current_Position = 0;
}

bool CDataBaseRecordSet::IsEOF()
{
	if (m_Record_Table.empty()) return true;
	int n = (int) m_Record_Table.begin()->second.size();
	auto bEOF = (m_Current_Position - n) >= 0;
	return (bEOF) ;
}
int CDataBaseRecordSet::FieldCount()
{
	int iCount = (int) m_Record_Table.size();
	return iCount;
}
void CDataBaseRecordSet::SetRecordFieldValue(wstring szField, vector<shared_ptr<CCompatibilityVariant>> Column)
{
	m_Record_Table[szField] = Column;
}