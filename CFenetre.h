#pragma once
#include <windows.h>
class CFenetre
{
protected:
	// Handle sur le hWnd de l'API
	HWND m_hWnd;
public:
	// Pull le Handle  de l'API

	HWND GethWnd();

	// Pull le Handle  de l'API
	void SethWnd(HWND hWnd);

	virtual void Create(HINSTANCE hInst,long style ,HWND hParent, int left, int top, int width, int height);

	static LRESULT fenetreProc(HWND hWnd, UINT msg, WPARAM wPAram, LPARAM lParam);

	virtual LRESULT virtualFenetreProc(HWND hWnd, UINT msg, WPARAM wPAram, LPARAM lParam);

};

