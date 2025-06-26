#ifndef ACHILDWINDOW_CPP
#define ACHILDWINDOW_CPP

#include "AChildWindow.h"

namespace WinDevTools {

	namespace GUI {

		AChildWindowW::AChildWindowW(LPCWSTR _lpszClassName, DWORD _dwStyle, HICON _hIcon, HCURSOR _hCursor, HBRUSH _hbrBackground, HICON _hIconSm, int _cbClsExtra, int _cbWndExtra, HINSTANCE _hInstance):
			AWindowW(_lpszClassName, _dwStyle, _hIcon, NULL, _hCursor, _hbrBackground, _hIcon, _cbClsExtra, _cbWndExtra, _hInstance),
			m_hWndParent(NULL)
		{
		}

		const HWND AChildWindowW::create(HWND _hWndParent, int _iWidth, int _iHeight, LPCWSTR _lpszWindowName, int _iX, int _iY, DWORD _dwStyle, HMENU _hMenu, DWORD _dwExStyle)
		{
			if(!m_hWndParent)
				m_hWndParent = _hWndParent;
			return AWindowW::create(_iWidth, _iHeight, _lpszWindowName, _hWndParent, _iX, _iY, _dwStyle | WS_CHILD, _hMenu, _dwExStyle);
		}
	}
}

#endif // !ACHILDWINDOW_CPP