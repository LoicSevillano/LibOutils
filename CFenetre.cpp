#include "CFenetre.h"

	// Pull le Handle  de l'API

HWND CFenetre::GethWnd()
{
	return m_hWnd;
}

	// Pull le Handle  de l'API
void CFenetre::SethWnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

void CFenetre::Create(HINSTANCE hInst,long style, HWND hParent, int left, int top , int width, int height )
{
	WNDCLASS wc = { };

	wc.lpfnWndProc = fenetreProc;
	wc.hInstance = hInst;
	wc.lpszClassName = L"FENETRE";

	RegisterClass(&wc);

    m_hWnd = CreateWindowEx(0, L"FENETRE", L"", style, left, top, width, height, hParent, NULL, hInst, this);
}

LRESULT CFenetre::fenetreProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    if (msg == WM_NCCREATE || msg == WM_INITDIALOG)
    {

        CREATESTRUCTW* c = (CREATESTRUCTW*)lParam;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)c->lpCreateParams);
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    CFenetre* pVue = (CFenetre*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    return pVue->virtualFenetreProc(hWnd,msg, wParam, lParam);

  

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CFenetre::virtualFenetreProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
