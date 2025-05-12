#include <stdexcept>

#include "Window.h"

namespace WinDevTools {

	namespace GUI {

		Window::Window(LPCWSTR _lpszClassName, DWORD _dwStyle, HICON _hIcon, LPCWSTR _lpszMenuName, HCURSOR _hCursor, HBRUSH _hbrBackground, HICON _hIconSm, int _cbClsExtra, int _cbWndExtra, HINSTANCE _hInstance):
			m_hInstance(_hInstance),
			m_lpszClassName(_lpszClassName),
			m_hWnd(NULL)
		{
			WNDCLASSEX wcex;
			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.cbClsExtra = _cbClsExtra;
			wcex.cbWndExtra = _cbWndExtra + 8;
			wcex.hbrBackground = _hbrBackground;
			wcex.hCursor = _hCursor;
			wcex.hIcon = _hIcon;
			wcex.hIconSm = _hIconSm;
			wcex.hInstance = m_hInstance;
			wcex.lpfnWndProc = S_WndProc;
			wcex.lpszClassName = m_lpszClassName;
			wcex.lpszMenuName = _lpszMenuName;
			wcex.style = _dwStyle;

			DWORD dwLastError;
			if(!RegisterClassEx(&wcex))
			{
				dwLastError = GetLastError();
				switch(dwLastError)
				{
					case ERROR_CLASS_ALREADY_EXISTS:
						break;
					default:
						DebugBreak();
				}
			}
		}

		const HWND Window::create(int _iWidth, int _iHeight, LPCWSTR _lpszWindowName, HWND _hWndParent, int _iX, int _iY, DWORD _dwStyle, HMENU _hMenu, DWORD _dwExStyle)
		{
			m_hWnd = CreateWindowEx(_dwExStyle, m_lpszClassName, _lpszWindowName, _dwStyle, _iX, _iY, _iWidth, _iHeight, _hWndParent, _hMenu, m_hInstance, this);
			
			return m_hWnd;
		}

		void Window::show(void)
		{
			if(m_hWnd) ShowWindow(m_hWnd, SW_SHOW);
			else throw std::runtime_error("m_hWnd is null");
		}

		void Window::hide(void)
		{
			if(m_hWnd) ShowWindow(m_hWnd, SW_HIDE);
			else throw std::runtime_error("m_hWnd is null");
		}

		void Window::update(void)
		{
			if(m_hWnd) UpdateWindow(m_hWnd);
			else throw std::runtime_error("m_hWnd is null");
		}

		LRESULT Window::Thunk(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
		{
			Window* pThis = (Window*)GetWindowLongPtr(_hWnd, GWLP_USERDATA);
			if(pThis) return pThis->WndProc(_hWnd, _uiMsg, _wParam, _lParam);
			else return DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam);
		}

		LRESULT Window::S_WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
		{
			if(_uiMsg == WM_NCCREATE)
			{
				CREATESTRUCT* pCS = (CREATESTRUCT*)_lParam;
				SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)(pCS->lpCreateParams));
				return DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam);
			}
			return Thunk(_hWnd, _uiMsg, _wParam, _lParam);
		}
	}
}