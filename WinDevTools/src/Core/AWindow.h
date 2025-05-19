#pragma once

#ifndef AWINDOW_H
#define AWINDOW_H

#include <Windows.h>
#include <vector>
#include <string>

namespace WinDevTools {

	namespace GUI {

		class AWindowW
		{
			public:
				AWindowW(LPCWSTR _lpszClassName = L"MyWindowClass", DWORD _dwStyle = CS_HREDRAW | CS_VREDRAW, HICON _hIcon = LoadIcon(NULL, IDI_APPLICATION), LPCWSTR _lpszMenuName = NULL, HCURSOR _hCursor = LoadCursor(NULL, IDC_ARROW), HBRUSH _hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH), HICON _hIconSm = NULL, int _cbClsExtra = 0, int _cbWndExtra = 0, HINSTANCE _hInstance = GetModuleHandle(NULL));
				const HWND create(int _iWidth, int _iHeight, LPCWSTR _lpszWindowName = L"MyWindow", HWND _hWndParent = NULL, int _iX = CW_USEDEFAULT, int _iY = CW_USEDEFAULT, DWORD _dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE, HMENU _hMenu = NULL, DWORD _dwExStyle = 0);

				void show(void);
				void hide(void);
				void update(void);

				const HINSTANCE getInstance(void) const { return m_hInstance; }
				const LPCWSTR getClassName(void) const { return m_lpszClassName; }
				const HWND getHandle(void) const { return m_hWnd; }

			protected:
				virtual LRESULT WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam) = 0;

			private:
				static LRESULT Thunk(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam);
				static LRESULT CALLBACK S_WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam);

				static const std::vector<std::wstring> s_szSystemClassNames;

				HINSTANCE m_hInstance;
				LPCWSTR m_lpszClassName;
				HWND m_hWnd;

		};

	}

}

#ifdef _UNICODE
	#define AWindow AWindowW
#else
	#define AWindow
#endif

#ifndef AWINDOW_CPP
#include "AWindow.cpp"
#endif // !AWINDOW_CPP

#endif // !AWINDOW_H