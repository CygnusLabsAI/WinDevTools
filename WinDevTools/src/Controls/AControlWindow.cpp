#ifndef ACONTROLWINDOW_CPP
#define ACONTROLWINDOW_CPP

#include "AControlWindow.h"

namespace WinDevTools {

	namespace GUI {

		AControlWindowW::AControlWindowW(LPCWSTR _lpszClassName):
			AChildWindowW(_lpszClassName)
		{
		}

		const HWND AControlWindowW::create(HWND _hWndParent, int _iWidth, int _iHeight, LPCWSTR _lpszWindowName, int _iX, int _iY, DWORD _dwStyle, DWORD _dwExStyle, HMENU _hID)
		{
			m_hID = _hID;
			return AChildWindowW::create(_hWndParent, _iWidth, _iHeight, _lpszWindowName, _iX, _iY, _dwStyle, _hID, _dwExStyle);
		}
	}
}

#endif // !ACONTROLWINDOW_CPP
