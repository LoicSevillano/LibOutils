#include "CDialog.h"
using namespace std;

CDialog::CDialog()
{
}
CDialog::~CDialog()
{

}

DLGPROC CDialog::dialog_procedure(UINT msg, WPARAM wParam, LPARAM lParam)
{
	int wmId = NULL, wmEvent = NULL;

	switch (msg)
	{
	case WM_INITDIALOG:
		initDialog();
		break;

	case WM_COMMAND:
		if (!lParam)
		{
			wmId = HIWORD(wParam);
			wmEvent = LOWORD(wParam);
		}
		else
		{
			wmId = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
		}

		if (wmId == IDOK) EndDialog(getwnd(), 1);
		else if (wmId == IDCANCEL) EndDialog(getwnd(), 1);
		switch (wmEvent)
		{
		case LBN_SELCHANGE:
			break;
		}
		break;

	case WM_DESTROY:
		EndDialog(getwnd(), 1);
		return 0;
		break;
	}
	return 0;

}

void CDialog::initDialog()
{



}

DLGPROC CDialog::dialog_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE || msg == WM_INITDIALOG)
	{
		///		CREATESTRUCT* c = (CREATESTRUCT*)lParam;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)lParam);
		CDialog* pClient = (CDialog*)lParam;
		if (pClient) pClient->m_hWnd = hWnd;
		if (msg == WM_INITDIALOG) pClient->dialog_procedure(msg, wParam, lParam);
		return 0;
	}
	CDialog* pClient = (CDialog*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (pClient) pClient->dialog_procedure(msg, wParam, lParam);
}