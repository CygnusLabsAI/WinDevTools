#pragma once

#ifndef ACONTROLWINDOW_H
#define ACONTROLWINDOW_H

#include "Core/AChildWindow.h"

namespace WinDevTools {

	namespace GUI {

		class AControlWindowW: public AChildWindowW
		{
			public:
				AControlWindowW(LPCWSTR _lpszClassName = L"MyControlWindowClass");
				const HWND create(HWND _hWndParent, int _iWidth, int _iHeight, LPCWSTR _lpszWindowName = L"MyControlWindow", int _iX = CW_USEDEFAULT, int _iY = CW_USEDEFAULT, DWORD _dwStyle = WS_CHILD | WS_VISIBLE, DWORD _dwExStyle = 0, HMENU _hMenuID = NULL);

				// Text Setting and Retrieving

				UINT getText(UINT _uiStrLenZT, LPWSTR _szBuffer);
				UINT getTextLength(void);
				bool setText(LPCWSTR _lpszText);

				// Font Setting and Retrieving

				HFONT getFont(void);
				void setFont(HFONT _hFont = NULL, bool _bRedraw = true);

				// Text and Background Color
				void setTextColor(COLORREF _Color);
				void setBGColor(COLORREF _Color);

				UINT getCtrlID(void) { return (UINT)m_hID; }

			protected:
				virtual LRESULT WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam) = 0;

				HMENU m_hID;
				COLORREF m_TextColor;
				COLORREF m_BkColor;
		};
	}

}

#ifdef _UNICODE
	#define AControlWindow AControlWindowW
#else
	#define AControlWindow
#endif

#ifndef ACONTROLWINDOW_CPP
#include "AControlWindow.cpp"
#endif // !ACONTROLWINDOW_CPP

#endif // !ACONTROLWINDOW_H
