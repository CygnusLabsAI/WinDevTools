#ifndef BUTTONCONTROL_CPP
#define BUTTONCONTROL_CPP

#include "ButtonControl.h"

namespace WinDevTools {

	namespace GUI {

		namespace Control {

			ButtonControlW::ButtonControlW(void):
				AControlWindowW(L"BUTTON")
			{
			}

			const HWND ButtonControlW::create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle, LPCWSTR _lpszWindowName)
			{
				return AControlWindowW::create(_hWndParent, _iWidth, _iHeight, _lpszWindowName, _iX, _iY, _dwStyle | WS_VISIBLE | WS_BORDER, _dwExStyle, _hID);
			}

			const HWND ButtonControlW::create(HWND _hWndParent, int _iX, int _iY, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle)
			{
				return create(_hWndParent, _iX, _iY, 100, 20, _hID, _dwStyle, _dwExStyle, L"");
			}

			const HWND ButtonControlW::create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle)
			{
				return create(_hWndParent, _iX, _iY, _iWidth, _iHeight, _hID, _dwStyle, _dwExStyle, L"");
			}

			LRESULT ButtonControlW::WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
			{
				return DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam);
			}
		}
	}
}

#endif // !BUTTONCONTROL_CPP
