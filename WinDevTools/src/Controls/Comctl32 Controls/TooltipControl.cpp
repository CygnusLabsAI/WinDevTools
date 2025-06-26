#ifndef TOOLTIPCONTROL_CPP
#define TOOLTIPCONTROL_CPP

#include "TooltipControl.h"

namespace WinDevTools {

	namespace GUI {

		namespace Control {

			TooltipControlW::TooltipControlW(void):
				APopupWindowW(TOOLTIPS_CLASSW)
			{

			}

			HWND TooltipControlW::create(HWND _hWndToolParent, DWORD _dwStyle)
			{
				HWND hWnd = APopupWindowW::create(_hWndToolParent, CW_USEDEFAULT, CW_USEDEFAULT, NULL, CW_USEDEFAULT, CW_USEDEFAULT, _dwStyle, WS_EX_TOOLWINDOW);
				SetWindowPos(getHandle(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

				return hWnd;
			}

			void TooltipControlW::activate(bool _bValue)
			{
				SendMessage(getHandle(), TTM_ACTIVATE, (WPARAM)_bValue, NULL);
			}

			bool TooltipControlW::addTool(HWND _hWndTool, const std::wstring& _szText, UINT _uiFlags)
			{
				TOOLINFOW ti = { 0 };
				ti.cbSize = TTTOOLINFOW_V1_SIZE;	// Need to use TTTOOLINFOW_V1_SIZE (or TTTOOLINFOW_V2_SIZE) instead of sizeof(TOOLINFOW), Not sure why, but doesn't work otherwise...
				ti.uFlags = _uiFlags;
				ti.hwnd = GetParent(_hWndTool);
				ti.uId = (UINT_PTR)_hWndTool;
				GetClientRect(_hWndTool, &ti.rect);
				//ti.rect = { 0, 0, 50, 50 };		// TODO: Add Rect support
				ti.hinst = getInstance();
				WCHAR* buffer = new WCHAR[_szText.size() + 1];
				wcscpy_s(buffer, _szText.size() + 1, _szText.c_str());
				ti.lpszText = buffer;
				buffer = nullptr;
				ti.lParam = NULL;				// TODO: Add LPARAM support
				ti.lpReserved = NULL;
				
				return SendMessage(getHandle(), TTM_ADDTOOLW, NULL, (LPARAM)&ti);
			}

			bool TooltipControlW::adjustRect(RECT& _rect, bool _bWndRect)
			{
				return SendMessage(getHandle(), TTM_ADJUSTRECT, (WPARAM)_bWndRect, (LPARAM)&_rect);
			}

			void TooltipControlW::delTool(HWND _hWndTool)
			{
				TOOLINFOW ti = { 0 };
				ti.cbSize = TTTOOLINFOW_V1_SIZE;	// Need to use TTTOOLINFOW_V1_SIZE (or TTTOOLINFOW_V2_SIZE) instead of sizeof(TOOLINFOW), Not sure why, but doesn't work otherwise...
				ti.uFlags = TTF_IDISHWND;
				ti.hwnd = GetParent(_hWndTool);
				ti.uId = (UINT_PTR)_hWndTool;

				SendMessage(getHandle(), TTM_DELTOOLW, NULL, (LPARAM)&ti);
			}

			DWORD TooltipControlW::getBubbleSize(void)
			{
				TOOLINFO ti = { 0 };
				return SendMessage(getHandle(), TTM_GETBUBBLESIZE, NULL, (LPARAM)&ti);
			}

			bool TooltipControlW::getCurrentTool(TOOLINFOW* _ti)
			{
				return SendMessage(getHandle(), TTM_GETCURRENTTOOLW, NULL, (LPARAM)_ti);
			}

			int TooltipControlW::getDelayTime(uint8_t _uiTTDTFlag)
			{
				return SendMessage(getHandle(), TTM_GETDELAYTIME, (WPARAM)_uiTTDTFlag, NULL);
			}

			void TooltipControlW::getMargin(RECT& _rectMargin)
			{
				SendMessage(getHandle(), TTM_GETMARGIN, NULL, (LPARAM)&_rectMargin);
			}

			int TooltipControlW::getMaxTipWidth(void)
			{
				return SendMessage(getHandle(), TTM_GETMAXTIPWIDTH, NULL, NULL);
			}

			void TooltipControlW::getText(HWND _hWndTool, LPWSTR _pszBuffer, size_t _uiNumTCHARs)
			{
				TOOLINFOW ti = { 0 };
				ti.cbSize = TTTOOLINFOW_V1_SIZE;
				ti.uFlags = TTF_IDISHWND;
				ti.hwnd = GetParent(_hWndTool);
				ti.uId = (UINT_PTR)_hWndTool;
				ti.lpszText = _pszBuffer;

				SendMessage(getHandle(), TTM_GETTEXTW, (WPARAM)_uiNumTCHARs, (LPARAM)&ti);
			}

			COLORREF TooltipControlW::getTipBkColor(void)
			{
				return SendMessage(getHandle(), TTM_GETTIPBKCOLOR, NULL, NULL);
			}

			COLORREF TooltipControlW::getTipTextColor(void)
			{
				return SendMessage(getHandle(), TTM_GETTIPTEXTCOLOR, NULL, NULL);
			}

			void TooltipControlW::getTitle(TTGETTITLE& _ttgt)
			{
				SendMessage(getHandle(), TTM_GETTITLE, NULL, (LPARAM)&_ttgt);
			}

			UINT TooltipControlW::getToolCount(void)
			{
				return SendMessage(getHandle(), TTM_GETTOOLCOUNT, NULL, NULL);
			}

			bool TooltipControlW::getToolInfo(HWND _hWndTool, TOOLINFOW& _ti)
			{
				_ti.cbSize = TTTOOLINFOW_V1_SIZE;
				_ti.uFlags = TTF_IDISHWND;
				_ti.hwnd = GetParent(_hWndTool);
				_ti.uId = (UINT_PTR)_hWndTool;
				_ti.lpszText = new WCHAR[80];		// See TTM_SETTOOLINFO Remarks entry in Windows API documentation

				return SendMessage(getHandle(), TTM_GETTOOLINFOW, NULL, (LPARAM)&_ti);
			}

			bool TooltipControlW::hitTest(HWND _hWndTool, POINT _pt, TTHITTESTINFOW& _tthti)
			{
				_tthti.hwnd = _hWndTool;
				_tthti.pt = _pt;
				_tthti.ti.cbSize = TTTOOLINFOW_V1_SIZE;
				return SendMessage(getHandle(), TTM_HITTESTW, NULL, (LPARAM)&_tthti);
			}

			void TooltipControlW::newToolRect(HWND _hWndTool, RECT _rect)
			{
				TOOLINFOW ti = { 0 };
				ti.cbSize = TTTOOLINFOW_V1_SIZE;
				ti.uFlags = TTF_IDISHWND;
				ti.hwnd = GetParent(_hWndTool);
				ti.uId = (UINT_PTR)_hWndTool;
				ti.rect = _rect;
				SendMessage(getHandle(), TTM_NEWTOOLRECTW, NULL, (LPARAM)&ti);
			}

			void TooltipControlW::pop(void)
			{
				SendMessage(getHandle(), TTM_POP, NULL, NULL);
			}

			void TooltipControlW::popUp(void)
			{
				SendMessage(getHandle(), TTM_POPUP, NULL, NULL);
			}

			void TooltipControlW::relayEvent(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
			{
				MSG msg;
				msg.hwnd = _hWnd;
				msg.message = _uiMsg;
				msg.wParam = _wParam;
				msg.lParam = _lParam;

				SendMessage(getHandle(), TTM_RELAYEVENT, NULL, (LPARAM)&msg);
			}

			void TooltipControlW::setDelayTime(uint16_t _uiNumMilliseconds, uint8_t _uiFlag)
			{
				SendMessage(getHandle(), TTM_SETDELAYTIME, (WPARAM)_uiFlag, MAKELPARAM(_uiNumMilliseconds, 0));
			}

			void TooltipControlW::setMargin(RECT& _rect)
			{
				SendMessage(getHandle(), TTM_SETMARGIN, NULL, (LPARAM)&_rect);
			}

			int TooltipControlW::setMaxTipWidth(int _iWidth)
			{
				return SendMessage(getHandle(), TTM_SETMAXTIPWIDTH, NULL, (LPARAM)_iWidth);
			}

			void TooltipControlW::setTipBkColor(COLORREF _Colorref)
			{
				SendMessage(getHandle(), TTM_SETTIPBKCOLOR, (WPARAM)_Colorref, NULL);
			}

			void TooltipControlW::setTipTextColor(COLORREF _Colorref)
			{
				SendMessage(getHandle(), TTM_SETTIPTEXTCOLOR, (WPARAM)_Colorref, NULL);
			}

			bool TooltipControlW::setTitle(LPWSTR _lpszTitle, HICON _hIcon)
			{
				return SendMessage(getHandle(), TTM_SETTITLEW, (WPARAM)_hIcon, (LPARAM)_lpszTitle);
			}

			void TooltipControlW::setToolInfo(HWND _hWndTool, TOOLINFOW& _ti)
			{
				if(_ti.cbSize == 0) _ti.cbSize = TTTOOLINFOW_V1_SIZE;
				TOOLINFOW ti = { 0 };
				getToolInfo(_hWndTool, ti);
				if(_ti.hwnd) ti.hwnd = _ti.hwnd;
				if(_ti.uId) ti.uId = _ti.uId;
				if(_ti.uFlags) ti.uFlags = _ti.uFlags;
				if(_ti.rect.left ||
				   _ti.rect.top ||
				   _ti.rect.right ||
				   _ti.rect.bottom) ti.rect = _ti.rect;
				if(_ti.hinst) ti.hinst = _ti.hinst;
				if(_ti.lpszText) ti.lpszText = _ti.lpszText;
				if(_ti.lParam) ti.lParam = _ti.lParam;
				if(_ti.lpReserved) ti.lpReserved = _ti.lpReserved;
				SendMessage(getHandle(), TTM_SETTOOLINFOW, NULL, (LPARAM)&ti);
			}

			void TooltipControlW::setWindowTheme(LPWSTR _lpszVisualStyle)
			{
				SendMessage(getHandle(), TTM_SETWINDOWTHEME, NULL, (LPARAM)_lpszVisualStyle);
			}

			void TooltipControlW::trackActivate(HWND _hWndTool, bool _bValue)
			{
				TOOLINFOW ti = { 0 };
				ti.cbSize = TTTOOLINFOW_V1_SIZE;
				ti.uFlags = TTF_IDISHWND;
				ti.hwnd = GetParent(_hWndTool);
				ti.uId = (UINT_PTR)_hWndTool;

				SendMessage(getHandle(), TTM_TRACKACTIVATE, (WPARAM)_bValue, (LPARAM)&ti);
			}

			void TooltipControlW::trackPosition(int16_t _iX, int16_t _iY)
			{
				SendMessage(getHandle(), TTM_TRACKPOSITION, NULL, MAKELPARAM(_iX, _iY));
			}

			void TooltipControlW::trackPosition(POINT& _pt)
			{
				trackPosition(_pt.x, _pt.y);
			}

			void TooltipControlW::update(void)
			{
				SendMessage(getHandle(), TTM_UPDATE, NULL, NULL);
			}

			void TooltipControlW::updateTipText(HWND _hWndTool, LPWSTR _lpszText)
			{
				TOOLINFOW ti = { 0 };
				if(getToolInfo(_hWndTool, ti))
				{
					delete ti.lpszText;
					ti.lpszText = nullptr;
					ti.lpszText = _lpszText;
					SendMessage(getHandle(), TTM_UPDATETIPTEXTW, NULL, (LPARAM)&ti);
				}
			}

			LRESULT TooltipControlW::WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
			{
				switch(_uiMsg)
				{
					case TTM_ADDTOOLW:
						break;
				}
				return DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam);
			}
		}
	}
}

#endif // !TOOLTIPCONTROL_CPP
