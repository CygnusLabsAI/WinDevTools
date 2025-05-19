#pragma once

#ifndef ACHILDWINDOW_H
#define ACHILDWINDOW_H

#include "AWindow.h"

namespace WinDevTools {

	namespace GUI {

		class AChildWindowW: public AWindowW
		{
			public:
				AChildWindowW(LPCWSTR _lpszClassName = L"MyChildWindowClass", DWORD _dwStyle = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, HICON _hIcon = LoadIcon(NULL, IDI_APPLICATION), HCURSOR _hCursor = LoadCursor(NULL, IDC_ARROW), HBRUSH _hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH), HICON _hIconSm = NULL, int _cbClsExtra = 0, int _cbWndExtra = 0, HINSTANCE _hInstance = GetModuleHandle(NULL));
				const HWND create(HWND _hWndParent, int _iWidth, int _iHeight, LPCWSTR _lpszWindowName = L"MyChildWindow", int _iX = CW_USEDEFAULT, int _iY = CW_USEDEFAULT, DWORD _dwStyle = WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, HMENU _hMenu = NULL, DWORD _dwExStyle = 0);

				const HWND getParentHandle(void) const { return m_hWndParent; }

			protected:
				virtual LRESULT WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam) = 0;

			private:
				HWND m_hWndParent;
		};
	}
}

#ifdef _UNICODE
	#define AChildWindow AChildWindowW
#else
	#define AChildWindow
#endif

#ifndef ACHILDWINDOW_CPP
#include "AChildWindow.cpp"
#endif // !ACHILDWINDOW_CPP

#endif // !ACHILDWINDOW_H