#include "ChildWindow.h"

namespace WinDevTools {

	namespace GUI {

		ChildWindow::ChildWindow(LPCWSTR _lpszClassName, DWORD _dwStyle, HICON _hIcon, HCURSOR _hCursor, HBRUSH _hbrBackground, HICON _hIconSm, int _cbClsExtra, int _cbWndExtra, HINSTANCE _hInstance):
			Window(_lpszClassName, _dwStyle, _hIcon, NULL, _hCursor, _hbrBackground, _hIcon, _cbClsExtra, _cbWndExtra, _hInstance),
			m_hWndParent(NULL)
		{
		}
		const HWND ChildWindow::create(HWND _hWndParent, int _iWidth, int _iHeight, LPCWSTR _lpszWindowName, int _iX, int _iY, DWORD _dwStyle, DWORD _dwExStyle)
		{
			m_hWndParent = _hWndParent;
			return Window::create(_iWidth, _iHeight, _lpszWindowName, _hWndParent, _iX, _iY, _dwStyle | WS_CHILD, NULL, _dwExStyle);
		}
	}
}