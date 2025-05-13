#pragma once

#ifndef ACONTROLWINDOW_H
#define ACONTROLWINDOW_H

#include "Core/AChildWindow.h"

namespace WinDevTools {

	namespace GUI {

		class AControlWindow: public AChildWindow
		{
			public:
				AControlWindow(LPCWSTR _lpszClassName = L"MyControlWindowClass");
				const HWND create(HWND _hWndParent, int _iWidth, int _iHeight, LPCWSTR _lpszWindowName = L"MyControlWindow", int _iX = CW_USEDEFAULT, int _iY = CW_USEDEFAULT, DWORD _dwStyle = WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, DWORD _dwExStyle = 0);

			protected:
				virtual LRESULT WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam) = 0;
		};
	}

}


#ifndef ACONTROLWINDOW_CPP
#include "AControlWindow.cpp"
#endif // !ACONTROLWINDOW_CPP

#endif // !ACONTROLWINDOW_H
