#ifndef AWINDOW_CPP
#define AWINDOW_CPP

#include <stdexcept>
#include "AWindow.h"
#include "WDTWndMgmt.h"
#ifdef WDT_USE_COMCTL32_CONTROLS
	#pragma comment(lib, "Comctl32.lib")
	#include <CommCtrl.h>
#endif // WDT_USE_COMCTL32_CONTROLS


namespace WinDevTools {

	namespace GUI {

#ifdef _INC_COMMCTRL
		const std::vector<std::wstring> AWindowW::s_szSystemClassNames = { ANIMATE_CLASS,  TEXT("BUTTON"), TEXT("COMBOBOX"), DATETIMEPICK_CLASS, TEXT("EDIT"), HOTKEY_CLASS, /*LINK_CLASS,*/ TEXT("LISTBOX"), TEXT("MDICLIENT"), MONTHCAL_CLASS, /*NATIVEFNTCTL_CLASS,*/ PROGRESS_CLASS, REBARCLASSNAME, TEXT("SCROLLBAR"), TEXT("STATIC"), STATUSCLASSNAME, TOOLBARCLASSNAME, TOOLTIPS_CLASS, TRACKBAR_CLASS, UPDOWN_CLASS, WC_BUTTON, WC_COMBOBOX, WC_COMBOBOXEX, WC_EDIT, WC_HEADER, WC_LISTBOX, WC_IPADDRESS, WC_LINK, WC_LISTVIEW, WC_NATIVEFONTCTL, WC_PAGESCROLLER, WC_SCROLLBAR, WC_STATIC, WC_TABCONTROL, WC_TREEVIEW};
#else
		const std::vector<std::wstring> AWindowW::s_szSystemClassNames = { TEXT("BUTTON"), TEXT("COMBOBOX"), TEXT("EDIT"), TEXT("LISTBOX"), TEXT("MDICLIENT"), TEXT("SCROLLBAR"), TEXT("STATIC") };
#endif // _INC_COMMCTRL

		AWindowW::AWindowW(LPCWSTR _lpszClassName, DWORD _dwStyle, HICON _hIcon, LPCWSTR _lpszMenuName, HCURSOR _hCursor, HBRUSH _hbrBackground, HICON _hIconSm, int _cbClsExtra, int _cbWndExtra, HINSTANCE _hInstance):
			m_hInstance(_hInstance),
			m_lpszClassName(_lpszClassName),
			m_hWnd(NULL)
		{
			auto it = std::find(s_szSystemClassNames.begin(), s_szSystemClassNames.end(), std::wstring(_lpszClassName));

			if(it == s_szSystemClassNames.end())
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
#ifdef _INC_COMMCTRL
			else
			{
				if(s_szSystemClassNames.size() > 5)
				{
					INITCOMMONCONTROLSEX icce;
					icce.dwSize = sizeof(INITCOMMONCONTROLSEX);
					icce.dwICC = 0;
					LPCWSTR pszWindowClassName = (*it).c_str();
					if(lstrcmp(pszWindowClassName, WC_LISTVIEWW) == 0) icce.dwICC |= ICC_LISTVIEW_CLASSES;
					if(lstrcmp(pszWindowClassName, WC_HEADERW) == 0) icce.dwICC |= ICC_LISTVIEW_CLASSES;
					if(lstrcmp(pszWindowClassName, TOOLTIPS_CLASSW) == 0) icce.dwICC |= ICC_WIN95_CLASSES;	// Is there a better way to include the Tooltip Control?
					if(lstrcmp(pszWindowClassName, WC_TREEVIEWW) == 0) icce.dwICC |= ICC_TREEVIEW_CLASSES;	// Includes Tooltip Control
					if(lstrcmp(pszWindowClassName, TOOLBARCLASSNAMEW) == 0) icce.dwICC |= ICC_BAR_CLASSES;	// Includes Tooltip Control
					if(lstrcmp(pszWindowClassName, STATUSCLASSNAMEW) == 0) icce.dwICC |= ICC_BAR_CLASSES;	// Includes Tooltip Control
					if(lstrcmp(pszWindowClassName, TRACKBAR_CLASSW) == 0) icce.dwICC |= ICC_BAR_CLASSES;	// Includes Tooltip Control
					if(lstrcmp(pszWindowClassName, WC_TABCONTROLW) == 0) icce.dwICC |= ICC_TAB_CLASSES;		// Includes Tooltip Control
					if(lstrcmp(pszWindowClassName, ANIMATE_CLASSW) == 0) icce.dwICC |= ICC_ANIMATE_CLASS;
					if(lstrcmp(pszWindowClassName, UPDOWN_CLASSW) == 0) icce.dwICC |= ICC_UPDOWN_CLASS;
					if(lstrcmp(pszWindowClassName, PROGRESS_CLASSW) == 0) icce.dwICC |= ICC_PROGRESS_CLASS;
					if(lstrcmp(pszWindowClassName, HOTKEY_CLASSW) == 0) icce.dwICC |= ICC_HOTKEY_CLASS;
					if(lstrcmp(pszWindowClassName, DATETIMEPICK_CLASSW) == 0) icce.dwICC |= ICC_DATE_CLASSES;
					if(lstrcmp(pszWindowClassName, WC_COMBOBOXEXW) == 0) icce.dwICC |= ICC_USEREX_CLASSES;
					if(lstrcmp(pszWindowClassName, REBARCLASSNAMEW) == 0) icce.dwICC |= ICC_COOL_CLASSES;
					if(lstrcmp(pszWindowClassName, WC_IPADDRESSW) == 0) icce.dwICC |= ICC_INTERNET_CLASSES;
					if(lstrcmp(pszWindowClassName, WC_PAGESCROLLERW) == 0) icce.dwICC |= ICC_PAGESCROLLER_CLASS;
					if(lstrcmp(pszWindowClassName, WC_NATIVEFONTCTLW) == 0) icce.dwICC |= ICC_NATIVEFNTCTL_CLASS;
					if(icce.dwICC)
					{
						if(!InitCommonControlsEx(&icce)) std::runtime_error("AWindowW::AWindowW() - InitCommonControlsEx failed");
					}
				}
			}
#endif // _INC_COMMCTRL
	
		}

		const HWND AWindowW::create(int _iWidth, int _iHeight, LPCWSTR _lpszWindowName, HWND _hWndParent, int _iX, int _iY, DWORD _dwStyle, HMENU _hMenu, DWORD _dwExStyle)
		{
			if(!m_hWnd)
				m_hWnd = CreateWindowEx(_dwExStyle, m_lpszClassName, _lpszWindowName, _dwStyle, _iX, _iY, _iWidth, _iHeight, _hWndParent, _hMenu, m_hInstance, this);
			
			if(m_hWnd)
			{
				if(!_hWndParent)
				{
					if(_dwStyle & WS_POPUP && WDT_POPUP_MGMT) WDT_SET_POPUP(this);
					else if(WDT_PARENT_MGMT) WDT_SET_PARENT(this);
				}
				else
				{
					if(_dwStyle & WS_CHILD)
					{
						if(std::find(s_szSystemClassNames.begin(), s_szSystemClassNames.end(), m_lpszClassName) != s_szSystemClassNames.end())
						{
							if(WDT_CONTROL_MGMT) WDT_SET_CONTROL(this);
						}
						else if(WDT_CHILD_MGMT) WDT_SET_CHILD(this);
					}
				}
			}
			return m_hWnd;
		}

		void AWindowW::show(void)
		{
			if(m_hWnd) ShowWindow(m_hWnd, SW_SHOW);
			else throw std::runtime_error("m_hWnd is null");
		}

		void AWindowW::hide(void)
		{
			if(m_hWnd) ShowWindow(m_hWnd, SW_HIDE);
			else throw std::runtime_error("m_hWnd is null");
		}

		void AWindowW::update(void)
		{
			if(m_hWnd) UpdateWindow(m_hWnd);
			else throw std::runtime_error("m_hWnd is null");
		}

		bool AWindowW::setPosition(HWND _hWndInsertAfter, int _iX, int _iY, int _iWidth, int _iHeight, uint16_t _uiFlags)
		{
			return SetWindowPos(m_hWnd, _hWndInsertAfter, _iX, _iY, _iWidth, _iHeight, (UINT)_uiFlags);
		}

		LRESULT AWindowW::RedirectWndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
		{
#ifdef WDT_USE_WINDOW_MGMT
			if(_uiMsg == WM_DRAWITEM)
			{
				LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)_lParam;
				if(auto it = sg_WindowMap.find(pDIS->hwndItem) != sg_WindowMap.end())
					return sg_WindowMap[pDIS->hwndItem]->handleDRAWITEM(pDIS);
			}
			if(auto it = sg_WindowMap.find((HWND)_lParam) != sg_WindowMap.end())
			{
				switch(_uiMsg)
				{
					case WM_CTLCOLORMSGBOX:
						return sg_WindowMap[(HWND)_lParam]->handleCTLCOLORMSGBOX(_wParam);
					case WM_CTLCOLOREDIT:
						return sg_WindowMap[(HWND)_lParam]->handleCTLCOLOREDIT(_wParam);
					case WM_CTLCOLORLISTBOX:
						return sg_WindowMap[(HWND)_lParam]->handleCTLCOLORLISTBOX(_wParam);
					case WM_CTLCOLORBTN:
						return sg_WindowMap[(HWND)_lParam]->handleCTLCOLORBTN(_wParam);
					case WM_CTLCOLORDLG:
						return sg_WindowMap[(HWND)_lParam]->handleCTLCOLORDLG(_wParam);
					case WM_CTLCOLORSCROLLBAR:
						return sg_WindowMap[(HWND)_lParam]->handleCTLCOLORSCROLLBAR(_wParam);
					case WM_CTLCOLORSTATIC:
						return sg_WindowMap[(HWND)_lParam]->handleCTLCOLORSTATIC(_wParam);
				}
			}
#endif
			return WndProc(_hWnd, _uiMsg, _wParam, _lParam);
		}

		LRESULT AWindowW::Thunk(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
		{
			AWindowW* pThis = (AWindowW*)GetWindowLongPtr(_hWnd, GWLP_USERDATA);
			if(pThis)
			{
				switch(_uiMsg)
				{
					case WM_CTLCOLORMSGBOX:
					case WM_CTLCOLOREDIT:
					case WM_CTLCOLORLISTBOX:
					case WM_CTLCOLORBTN:
					case WM_CTLCOLORDLG:
					case WM_CTLCOLORSCROLLBAR:
					case WM_CTLCOLORSTATIC:
					case WM_DRAWITEM:
						return pThis->RedirectWndProc(_hWnd, _uiMsg, _wParam, _lParam);
					default:
						return pThis->WndProc(_hWnd, _uiMsg, _wParam, _lParam);
				} 			
			}
			else return DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam);
		}

		LRESULT AWindowW::S_WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
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

#endif // !AWINDOW_CPP