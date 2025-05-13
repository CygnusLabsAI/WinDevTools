#pragma once

#ifndef APOPUPWINDOW_H
#define APOPUPWINDOW_H

#include "AWindow.h"

namespace WinDevTools {

	namespace GUI {

		class APopupWindow: public AWindow
		{
		public:
			APopupWindow(LPCWSTR _lpszClassName = L"MyPopupWindowClass", DWORD _dwStyle = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, HICON _hIcon = LoadIcon(NULL, IDI_APPLICATION), HCURSOR _hCursor = LoadCursor(NULL, IDC_ARROW), HBRUSH _hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH), HICON _hIconSm = NULL, int _cbClsExtra = 0, int _cbWndExtra = 0, HINSTANCE _hInstance = GetModuleHandle(NULL));
			const HWND create(HWND _hWndParent, int _iWidth, int _iHeight, LPCWSTR _lpszWindowName = L"MyPopupWindow", int _iX = CW_USEDEFAULT, int _iY = CW_USEDEFAULT, DWORD _dwStyle = WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW, DWORD _dwExStyle = 0);

			const HWND getParentHandle(void) const { return m_hWndParent; }

		protected:
			virtual LRESULT WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam) = 0;

		private:
			HWND m_hWndParent;
		};
	}
}

#ifndef APOPUPWINDOW_CPP
#include "APopupWindow.cpp"
#endif // !APOPUPWINDOW_CPP

#endif // !APOPUPWINDOW_H