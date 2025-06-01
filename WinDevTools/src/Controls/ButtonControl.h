#pragma once

#ifndef BUTTONCONTROL_H
#define BUTTONCONTROL_H

#include "AControlWindow.h"

namespace WinDevTools {

	namespace GUI {

		namespace Control {

			class ButtonControlW: public AControlWindowW
			{
				public:
					ButtonControlW(void);
					const HWND create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle, LPCWSTR _lpszWindowName);
					const HWND create(HWND _hWndParent, int _iX, int _iY, HMENU _hID, DWORD _dwStyle = 0, DWORD _dwExStyle = 0);
					const HWND create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle = 0, DWORD _dwExStyle = 0);

					// Helper Functions

					bool isState(WORD _wStateFlag);
					COLORREF getSelectedTextColor(void) { return m_SelectedTextColor; }
					COLORREF getBorderColor(void) { return m_BorderColor; }
					void setSelectedTextColor(COLORREF _SelectedTextColor) { m_SelectedTextColor = _SelectedTextColor; }
					void setBorderColor(COLORREF _BorderColor) { m_BorderColor = _BorderColor; }

					// Control Message Functions
					
					void click(void);
					LRESULT getCheck(void);
					LRESULT getImage(UINT _uiImageType);
					LRESULT getState(void);
					void setCheck(UINT _uiCheckState);
					void setDontClick(bool _bValue);
					LRESULT setBitmapImage(HBITMAP _hBitmap);
					LRESULT setIconImage(HICON _hIcon);
					void setHighlight(bool _bValue);
					void setStyle(DWORD _dwStyle, bool _bRedraw = true);

					// WM_CTLCOLORBTN Handler
					virtual LRESULT handleCTLCOLORBTN(WPARAM _wParam) override;

					// WM_DRAWITEM Handler
					virtual LRESULT handleDRAWITEM(LPDRAWITEMSTRUCT _lpDrawItemStruct) override;

				protected:
					virtual LRESULT WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam) override;

					COLORREF m_SelectedTextColor;
					COLORREF m_BorderColor;

			};

		}
	}
}

#ifdef _UNICODE
	#define ButtonControl ButtonControlW
#else
	#define ButtonControl
#endif // _UNICODE

#ifdef WDT_USE_WINDOW_MGMT
	#define PtrButton(hwnd) ((WinDevTools::GUI::Control::ButtonControl*)sg_WindowMap[hwnd])
#endif // WDT_USE_WINDOW_MGMT

#ifndef BUTTONCONTROL_CPP
	#include "ButtonControl.cpp"
#endif // !BUTTONCONTROL_CPP

#endif // !BUTTONCONTROL_H
