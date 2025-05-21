#ifndef ACONTROLWINDOW_CPP
#define ACONTROLWINDOW_CPP

#include "AControlWindow.h"

namespace WinDevTools {

	namespace GUI {

		AControlWindowW::AControlWindowW(LPCWSTR _lpszClassName):
			AChildWindowW(_lpszClassName),
			m_hID(NULL),
			m_TextColor(RGB(0, 0, 0)),
			m_BkColor(RGB(255, 255, 255))
		{
		}

		const HWND AControlWindowW::create(HWND _hWndParent, int _iWidth, int _iHeight, LPCWSTR _lpszWindowName, int _iX, int _iY, DWORD _dwStyle, DWORD _dwExStyle, HMENU _hID)
		{
			m_hID = _hID;
			return AChildWindowW::create(_hWndParent, _iWidth, _iHeight, _lpszWindowName, _iX, _iY, _dwStyle, _hID, _dwExStyle);
		}

		UINT AControlWindowW::getText(UINT _uiStrLenZT, LPWSTR _szBuffer)
		{
			return SendMessage(getHandle(), WM_GETTEXT, (WPARAM)_uiStrLenZT, (LPARAM)_szBuffer);
		}

		UINT AControlWindowW::getTextLength(void)
		{
			return SendMessage(getHandle(), WM_GETTEXTLENGTH, NULL, NULL);
		}

		bool AControlWindowW::setText(LPCWSTR _lpszText)
		{
			return SendMessage(getHandle(), WM_SETTEXT, NULL, (LPARAM)_lpszText);
		}

		HFONT AControlWindowW::getFont(void)
		{
			return (HFONT)SendMessage(getHandle(), WM_GETFONT, NULL, NULL);
		}

		void AControlWindowW::setFont(HFONT _hFont, bool _bRedraw)
		{
			SendMessage(getHandle(), WM_SETFONT, (WPARAM)_hFont, MAKELPARAM(_bRedraw, NULL));
		}

		void AControlWindowW::setTextColor(COLORREF _Color)
		{
			m_TextColor = _Color;
		}

		void AControlWindowW::setBGColor(COLORREF _Color)
		{
			m_BkColor = _Color;
		}
	}
}

#endif // !ACONTROLWINDOW_CPP
