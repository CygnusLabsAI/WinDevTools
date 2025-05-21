#pragma once

#ifndef BUTTONCONTROL_H
#define BUTTONCONTROL_H

#include "AControlWindow.h"

namespace WinDevTools {

	namespace GUI {

		namespace Control {

			class ButtonControlW: public AControlWindowW
			{
				public:
					ButtonControlW(void);
					const HWND create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle, LPCWSTR _lpszWindowName);
					const HWND create(HWND _hWndParent, int _iX, int _iY, HMENU _hID, DWORD _dwStyle = 0, DWORD _dwExStyle = 0);
					const HWND create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle = 0, DWORD _dwExStyle = 0);

				protected:
					virtual LRESULT WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam);
			};

		}
	}
}

#ifdef _UNICODE
	#define ButtonControl ButtonControlW
#else
	#define ButtonControl
#endif // _UNICODE

#ifndef BUTTONCONTROL_CPP
	#include "ButtonControl.cpp"
#endif // !BUTTONCONTROL_CPP

#endif // !BUTTONCONTROL_H
