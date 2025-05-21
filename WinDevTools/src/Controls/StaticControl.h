#pragma once

#ifndef STATICCONTROL_H
#define STATICCONTROL_H

#include "AControlWindow.h"
namespace WinDevTools {

	namespace GUI {

		namespace Control {

			class StaticControlW: public AControlWindowW
			{
				public:
					StaticControlW(void);
					const HWND create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle, LPCWSTR _lpszWindowName);
					const HWND create(HWND _hWndParent, int _iX, int _iY, HMENU _hID, DWORD _dwStyle = 0, DWORD _dwExStyle = 0);
					const HWND create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle = 0, DWORD _dwExStyle = 0);

					// STM_GETIMAGE/STM_SETIMAGE wrappers

					HICON getIcon(void);
					HICON setIcon(HICON _hIcon);
					HBITMAP getBitmap(void);
					HBITMAP setBitmap(HBITMAP _hBitmap);
					HENHMETAFILE getEnhMetaFile(void);
					HENHMETAFILE setEngMetaFile(HENHMETAFILE _hEnhMetaFile);

					// WM_CTLCOLORSTATIC Handler
					virtual LRESULT handleCTLCOLORSTATIC(WPARAM _wParam) override;

				protected:
					virtual LRESULT WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam) override;
			};
		}
	}
}

#ifdef _UNICODE
	#define StaticControl StaticControlW
#else
	#define StaticControl
#endif // _UNICODE


#ifndef STATICCONTROL_CPP
	#include "StaticControl.cpp"
#endif // !STATICCONTROL_CPP

#endif // !STATICCONTROL_H
