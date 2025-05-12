#pragma once

#include <Windows.h>

namespace WinDevTools {

	namespace GUI {

		class Window
		{
			public:
				Window(LPCWSTR _lpszClassName = L"MyWindowClass", DWORD _dwStyle = CS_HREDRAW | CS_VREDRAW, HICON _hIcon = LoadIcon(NULL, IDI_APPLICATION), LPCWSTR _lpszMenuName = NULL, HCURSOR _hCursor = LoadCursor(NULL, IDC_ARROW), HBRUSH _hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH), HICON _hIconSm = NULL, int _cbClsExtra = 0, int _cbWndExtra = 0, HINSTANCE _hInstance = GetModuleHandle(NULL));
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

				HINSTANCE m_hInstance;
				LPCWSTR m_lpszClassName;
				HWND m_hWnd;

		};
	}
}