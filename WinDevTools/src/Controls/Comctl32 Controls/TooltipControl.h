#pragma once

#ifndef TOOLTIPCONTROL_H
#define TOOLTIPCONTROL_H

#include "Core/APopupWindow.h"
#include <CommCtrl.h>

namespace WinDevTools {

	namespace GUI {

		namespace Control {

			class TooltipControlW: public APopupWindow
			{
				public:
					TooltipControlW(void);
					HWND create(HWND _hWndToolParent, DWORD _dwStyle = TTS_NOPREFIX | TTS_ALWAYSTIP);

					// Tooltip Message Functions

					void activate(bool _bValue);
					bool addTool(HWND _hWndTool, const std::wstring& _szText, UINT _uiFlags = TTF_IDISHWND | TTF_SUBCLASS);
					bool adjustRect(RECT& _rect, bool _bWndRect);
					void delTool(HWND _hWndTool);
					DWORD getBubbleSize(void);
					bool getCurrentTool(TOOLINFOW* _ti = NULL);
					int getDelayTime(uint8_t _uiTTDTFlag);
					void getMargin(RECT& _rectMargin);
					int getMaxTipWidth(void);
					void getText(HWND _hWndTool, LPWSTR _pszBuffer, size_t _uiNumTCHARs);
					COLORREF getTipBkColor(void);
					COLORREF getTipTextColor(void);
					void getTitle(TTGETTITLE& _ttgt);	// Comclt32.dll 6.0; may require manifest.
					UINT getToolCount(void);
					bool getToolInfo(HWND _hWndTool, TOOLINFOW& _ti);
					bool hitTest(HWND _hWndTool, POINT _pt, TTHITTESTINFOW& _tthti);
					void newToolRect(HWND _hWndTool, RECT _rect);
					void pop(void);
					void popUp(void);	// Comclt32.dll 6.0; may require manifest.
					void relayEvent(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam);
					void setDelayTime(uint16_t _uiNumMilliseconds = -1, uint8_t _uiFlag = TTDT_AUTOMATIC);
					void setMargin(RECT& _rect);
					int setMaxTipWidth(int _iWidth = -1);
					void setTipBkColor(COLORREF _Colorref);
					void setTipTextColor(COLORREF _Colorref);
					bool setTitle(LPWSTR _lpszTitle, HICON _hIcon = TTI_NONE);
					void setToolInfo(HWND _hWndTool, TOOLINFOW& _lpti);
					void setWindowTheme(LPWSTR _lpszVisualStyle);	// Comclt32.dll 6.0; may require manifest
					void trackActivate(HWND _hWndTool, bool _bValue);
					void trackPosition(int16_t _iX, int16_t _iY);
					void trackPosition(POINT& _pt);
					void update(void);
					void updateTipText(HWND _hWndTool, LPWSTR _lpszText);
					// HWND windowFromPoint(LPPOINT _lppt);	// TODO: Determine if necessary for class
					




				protected:
					LRESULT WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam) override;

			};
		}
	}
}

#ifdef _UNICODE
	#define TooltipControl TooltipControlW
#else
	#define TooltipControl
#endif // _UNICODE

#ifdef WDT_USE_WINDOW_MGMT
	#define PtrTooltip(hwnd) ((WinDevTools::GUI::Control::TooltipControl*)sg_WindowMap[hwnd])
#endif // WDT_USE_WINDOW_MGMT

#ifndef TOOLTIPCONTROL_CPP
	#include "TooltipControl.cpp"
#endif // !TOOLTIPCONTROL_CPP

#endif // !TOOLTIPCONTROL_H
