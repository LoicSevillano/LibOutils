#pragma 
#include <Windows.h>

class Cfenetres 
{
	protected:
	// Handle sur la fenetre
	HWND m_hWnd;

	public:
		HWND getwnd();

		void setwnd(HWND hWnd);
};

