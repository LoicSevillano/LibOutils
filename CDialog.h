#pragma once
#include "Cfenetres.h"
class CDialog : public Cfenetres
{
public:
	CDialog();
	~CDialog();
	static DLGPROC dialog_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual DLGPROC dialog_procedure(UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void initDialog();

private:




};