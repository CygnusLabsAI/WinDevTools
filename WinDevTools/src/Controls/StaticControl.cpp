#ifndef STATICCONTROL_CPP
#define STATICCONTROL_CPP

#include "StaticControl.h"

namespace WinDevTools {

	namespace GUI {

		namespace Control {
			StaticControlW::StaticControlW(void):
				AControlWindowW(L"STATIC")
			{
			}

			const HWND StaticControlW::create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle, LPCWSTR _lpszWindowName)
			{
				return AControlWindowW::create(_hWndParent, _iWidth, _iHeight, _lpszWindowName, _iX, _iY, _dwStyle | WS_VISIBLE, _dwExStyle, _hID);
			}

			const HWND StaticControlW::create(HWND _hWndParent, int _iX, int _iY, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle)
			{
				return create(_hWndParent, _iX, _iY, 100, 20, _hID, _dwStyle, _dwExStyle, L"");
			}

			const HWND StaticControlW::create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle)
			{
				return create(_hWndParent, _iX, _iY, _iWidth, _iHeight, _hID, _dwStyle, _dwExStyle, L"");
			}

			HICON StaticControlW::getIcon(void)
			{
				return (HICON)SendMessage(getHandle(), STM_GETICON, NULL, NULL);
			}

			HICON StaticControlW::setIcon(HICON _hIcon)
			{
				return (HICON)SendMessage(getHandle(), STM_SETICON, (WPARAM)_hIcon, NULL);
			}

			HBITMAP StaticControlW::getBitmap(void)
			{
				return (HBITMAP)SendMessage(getHandle(), STM_GETIMAGE, IMAGE_BITMAP, NULL);
			}

			HBITMAP StaticControlW::setBitmap(HBITMAP _hBitmap)
			{
				return (HBITMAP)SendMessage(getHandle(), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)_hBitmap);
			}

			HENHMETAFILE StaticControlW::getEnhMetaFile(void)
			{
				return (HENHMETAFILE)SendMessage(getHandle(), STM_GETIMAGE, IMAGE_ENHMETAFILE, NULL);
			}

			HENHMETAFILE StaticControlW::setEngMetaFile(HENHMETAFILE _hEnhMetaFile)
			{
				return (HENHMETAFILE)SendMessage(getHandle(), STM_SETIMAGE, IMAGE_ENHMETAFILE, (LPARAM)_hEnhMetaFile);
			}

			LRESULT StaticControlW::handleCTLCOLORSTATIC(WPARAM _wParam)
			{
				SetTextColor((HDC)_wParam, m_TextColor);
				SetBkColor((HDC)_wParam, m_BkColor);
				return (LRESULT)((HBRUSH)GetStockObject(DC_BRUSH));
			}

			LRESULT StaticControlW::WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
			{
				return DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam);
			}
		}
	}
}

#endif // !STATICCONTROL_CPP
