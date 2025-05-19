#pragma once

#ifndef ACONTROLWINDOW_H
#define ACONTROLWINDOW_H

#include "Core/AChildWindow.h"

namespace WinDevTools {

	namespace GUI {

		class AControlWindowW: public AChildWindowW
		{
			public:
				AControlWindowW(LPCWSTR _lpszClassName = L"MyControlWindowClass");
				const HWND create(HWND _hWndParent, int _iWidth, int _iHeight, LPCWSTR _lpszWindowName = L"MyControlWindow", int _iX = CW_USEDEFAULT, int _iY = CW_USEDEFAULT, DWORD _dwStyle = WS_CHILD | WS_VISIBLE, DWORD _dwExStyle = 0, HMENU _hMenuID = NULL);

				UINT getCtrlID(void) { return (UINT)m_hID; }

			protected:
				virtual LRESULT WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam) = 0;

				HMENU m_hID;
		};
	}

}

#ifdef _UNICODE
	#define AControlWindow AControlWindowW
#else
	#define AControlWindow
#endif

#ifndef ACONTROLWINDOW_CPP
#include "AControlWindow.cpp"
#endif // !ACONTROLWINDOW_CPP

#endif // !ACONTROLWINDOW_H
