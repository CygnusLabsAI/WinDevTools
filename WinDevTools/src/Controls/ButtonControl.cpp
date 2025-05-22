#ifndef BUTTONCONTROL_CPP
#define BUTTONCONTROL_CPP

#include "ButtonControl.h"

namespace WinDevTools {

	namespace GUI {

		namespace Control {

			ButtonControlW::ButtonControlW(void):
				AControlWindowW(L"BUTTON")
			{
			}

			const HWND ButtonControlW::create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle, LPCWSTR _lpszWindowName)
			{
				return AControlWindowW::create(_hWndParent, _iWidth, _iHeight, _lpszWindowName, _iX, _iY, _dwStyle | WS_VISIBLE, _dwExStyle, _hID);
			}

			const HWND ButtonControlW::create(HWND _hWndParent, int _iX, int _iY, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle)
			{
				return create(_hWndParent, _iX, _iY, 100, 20, _hID, _dwStyle, _dwExStyle, L"");
			}

			const HWND ButtonControlW::create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle)
			{
				return create(_hWndParent, _iX, _iY, _iWidth, _iHeight, _hID, _dwStyle, _dwExStyle, L"");
			}

			void ButtonControlW::click(void)
			{
				SendMessage(getHandle(), BM_CLICK, NULL, NULL);
			}

			LRESULT ButtonControlW::getCheck(void)
			{
				return SendMessage(getHandle(), BM_GETCHECK, NULL, NULL);
			}

			LRESULT ButtonControlW::getImage(UINT _uiImageType)
			{
				return SendMessage(getHandle(), BM_GETIMAGE, (WPARAM)_uiImageType, NULL);
			}

			LRESULT ButtonControlW::getState(void)
			{
				return SendMessage(getHandle(), BM_GETSTATE, NULL, NULL);
			}

			void ButtonControlW::setCheck(UINT _uiCheckState)
			{
				SendMessage(getHandle(), BM_SETCHECK, (WPARAM)_uiCheckState, NULL);
			}

			void ButtonControlW::setDontClick(bool _bValue)
			{
				SendMessage(getHandle(), BM_SETDONTCLICK, (WPARAM)_bValue, NULL);
			}

			LRESULT ButtonControlW::setBitmapImage(HBITMAP _hBitmap)
			{
				return SendMessage(getHandle(), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)_hBitmap);
			}

			LRESULT ButtonControlW::setIconImage(HICON _hIcon)
			{
				return SendMessage(getHandle(), BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)_hIcon);
			}

			void ButtonControlW::setHighlight(bool _bValue)
			{
				SendMessage(getHandle(), BM_SETSTATE, (WPARAM)_bValue, NULL);
			}

			void ButtonControlW::setStyle(DWORD _dwStyle, bool _bRedraw)
			{
				SendMessage(getHandle(), BM_SETSTYLE, (WPARAM)_dwStyle, MAKELPARAM((BOOL)_bRedraw, NULL));
			}

			LRESULT ButtonControlW::handleCTLCOLORBTN(WPARAM _wParam)
			{
				SetTextColor((HDC)_wParam, m_TextColor);
				SetBkColor((HDC)_wParam, m_BkColor);
				return (LRESULT)((HBRUSH)GetStockObject(DC_BRUSH));
			}

			LRESULT ButtonControlW::WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
			{
				return DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam);
			}
		}
	}
}

#endif // !BUTTONCONTROL_CPP
