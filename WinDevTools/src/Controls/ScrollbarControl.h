#pragma once

#ifndef SCROLLBARCONTROL_H
#define SCROLLBARCONTROL_H

#include "AControlWindow.h"

namespace WinDevTools {

	namespace GUI {

		namespace Control {

			class ScrollbarControlW: public AControlWindowW
			{
				public:
					ScrollbarControlW(void);
					const HWND create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle = 0, DWORD _dwExStyle = 0);
					const HWND create(HWND _hWndParent, int _iX, int _iY, HMENU _hID, DWORD _dwStyle = 0, DWORD _dwExStyle = 0);
					//const HWND create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle = 0, DWORD _dwExStyle = 0);

					// Control Message Functions
					bool enableArrows(WORD _wFlag);
					bool getScrollbarInfo(LPSCROLLBARINFO _lpScrollbarInfo);
					bool getScrollInfo(LPSCROLLINFO _lpScrollInfo, WORD _wFlags = SIF_ALL);
					int setScrollInfo(LPSCROLLINFO _lpScrollInfo, WORD _wFlags, bool _bRedraw = true);
					int getPos(void);
					void setPos(int _iNewPos, bool _bRedraw = false);
					void getRange(int* _piMin, int* _piMax);
					void setRange(int _iMin, int _iMax, bool _bRedraw = false);
					int getPage(void);
					void setPage(int _iPage, bool _bRedraw = false);
					int getTrackPos(void);

					virtual LRESULT handleCTLCOLORSCROLLBAR(WPARAM _wParam) override;

				protected:
					virtual LRESULT WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam) override;

					HBRUSH m_hBarBrush;
			};
		}
	}
}

#ifdef _UNICODE
	#define ScrollbarControl ScrollbarControlW
#else
	#define ScrollbarControl
#endif // _UNICODE

#ifdef WDT_USE_WINDOW_MGMT
	#define PtrScrollbar(hwnd) ((WinDevTools::GUI::Control::ScrollbarControl*)sg_WindowMap[hwnd])
#endif // WDT_USE_WINDOW_MGMT


#ifndef SCROLLBARCONTROL_CPP
	#include "ScrollbarControl.cpp"
#endif // !SCROLLBARCONTROL_CPP


#endif // !SCROLLBARCONTROL_H
