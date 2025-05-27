#ifndef BUTTONCONTROL_CPP
#define BUTTONCONTROL_CPP

#include "ButtonControl.h"

namespace WinDevTools {

	namespace GUI {

		namespace Control {

			ButtonControlW::ButtonControlW(void):
				AControlWindowW(L"BUTTON"),
				m_SelectedTextColor(RGB(0,0,0)),
				m_BorderColor(RGB(0,0,0))
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

			bool ButtonControlW::isState(WORD _wStateFlag)
			{
				WORD state = getState() & (_wStateFlag > 0 ? _wStateFlag : 1);
				return (getState() & (_wStateFlag > 0 ? _wStateFlag : 1)) == _wStateFlag;
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

			LRESULT ButtonControlW::handleDRAWITEM(LPDRAWITEMSTRUCT _lpDrawItemStruct)
			{
				// The following code emulates the look of a windows 10 default push button

				HDC hdc = _lpDrawItemStruct->hDC;
				RECT rc = _lpDrawItemStruct->rcItem;
				UINT state = _lpDrawItemStruct->itemState;

				// Draw Border and Background
				HPEN hPen = CreatePen(PS_SOLID, 1, m_BorderColor);
				HBRUSH hBrush = CreateSolidBrush(m_BkColor);
				SelectObject(hdc, hPen);
				SelectObject(hdc, hBrush);
				Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
				DeleteObject(hPen);
				DeleteObject(hBrush);

				// BEGIN Emulated Windows 10 Button
				UINT8 RED = GetRValue(m_BkColor);
				UINT8 GREEN = GetGValue(m_BkColor);
				UINT8 BLUE = GetBValue(m_BkColor);
				COLORREF LT_OUTTER = RGB(RED + (RED / 16), GREEN + (GREEN / 16), BLUE + (BLUE / 16));
				COLORREF RB_OUTTER = RGB(((RED * 7) / 16), ((GREEN * 7) / 16), ((BLUE * 7) / 16));
				COLORREF LT_INNER = RGB(((RED * 227) / 240), ((GREEN * 227) / 240), ((BLUE * 227) / 240));
				COLORREF RB_INNER = RGB(((RED * 2) / 3), ((GREEN * 2) / 3), ((BLUE * 2) / 3));
				hBrush = CreateSolidBrush(m_BkColor);
				SelectObject(hdc, hBrush);
				FillRect(hdc, &rc, hBrush);
				DeleteObject(hBrush);

				if(state & ODS_SELECTED)
				{
					// LT-Outter Border
					hPen = CreatePen(PS_SOLID, 1, RB_OUTTER);
					SelectObject(hdc, hPen);
					MoveToEx(hdc, rc.left, rc.bottom - 2, NULL);
					LineTo(hdc, rc.left, rc.top);
					LineTo(hdc, rc.right - 1, rc.top);
					DeleteObject(hPen);

					// LT-Inner Border
					hPen = CreatePen(PS_SOLID, 1, RB_INNER);
					SelectObject(hdc, hPen);
					MoveToEx(hdc, rc.left + 1, rc.bottom - 3, NULL);
					LineTo(hdc, rc.left + 1, rc.top + 1);
					LineTo(hdc, rc.right - 2, rc.top + 1);
					DeleteObject(hPen);

					// RB-Outter Border
					hPen = CreatePen(PS_SOLID, 1, LT_OUTTER);
					SelectObject(hdc, hPen);
					MoveToEx(hdc, rc.left, rc.bottom - 1, NULL);
					LineTo(hdc, rc.right - 1, rc.bottom - 1);
					LineTo(hdc, rc.right - 1, rc.top - 1);
					DeleteObject(hPen);

					// RB-Inner Border
					hPen = CreatePen(PS_SOLID, 1, LT_INNER);
					SelectObject(hdc, hPen);
					MoveToEx(hdc, rc.left + 1, rc.bottom - 2, NULL);
					LineTo(hdc, rc.right - 2, rc.bottom - 2);
					LineTo(hdc, rc.right - 2, rc.top);
					DeleteObject(hPen);
				}
				else
				{
					// LT-Outter Border
					hPen = CreatePen(PS_SOLID, 1, LT_OUTTER);
					SelectObject(hdc, hPen);
					MoveToEx(hdc, rc.left, rc.bottom - 2, NULL);
					LineTo(hdc, rc.left, rc.top);
					LineTo(hdc, rc.right - 1, rc.top);
					DeleteObject(hPen);

					// LT-Inner Border
					hPen = CreatePen(PS_SOLID, 1, LT_INNER);
					SelectObject(hdc, hPen);
					MoveToEx(hdc, rc.left + 1, rc.bottom - 3, NULL);
					LineTo(hdc, rc.left + 1, rc.top + 1);
					LineTo(hdc, rc.right - 2, rc.top + 1);
					DeleteObject(hPen);

					// RB-Outter Border
					hPen = CreatePen(PS_SOLID, 1, RB_OUTTER);
					SelectObject(hdc, hPen);
					MoveToEx(hdc, rc.left, rc.bottom - 1, NULL);
					LineTo(hdc, rc.right - 1, rc.bottom - 1);
					LineTo(hdc, rc.right - 1, rc.top - 1);
					DeleteObject(hPen);

					// RB-Inner Border
					hPen = CreatePen(PS_SOLID, 1, RB_INNER);
					SelectObject(hdc, hPen);
					MoveToEx(hdc, rc.left + 1, rc.bottom - 2, NULL);
					LineTo(hdc, rc.right - 2, rc.bottom - 2);
					LineTo(hdc, rc.right - 2, rc.top);
					DeleteObject(hPen);
				}

				if(state & ODS_FOCUS)
				{
					//hPen = CreatePen(PS_DASH, 0, RGB(255 - RED, 255 - GREEN, 255 - BLUE));
					//hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
					LOGBRUSH lb;
					lb.lbColor = RGB(255 - RED, 255 - GREEN, 255 - BLUE);
					lb.lbStyle = BS_SOLID;

					hPen = ExtCreatePen(PS_COSMETIC | PS_ALTERNATE, 1, &lb, 0, NULL);
					hBrush = CreateSolidBrush(m_BkColor);
					SelectObject(hdc, hBrush);
					SelectObject(hdc, hPen);
					BOOL result = Rectangle(hdc, rc.left + 3, rc.top + 3, rc.right - 3, rc.bottom - 3);
					DeleteObject(hPen);
					DeleteObject(hBrush);
				}
				// END Emulated Windows 10 Button

				// Draw Text
				SetBkMode(hdc, TRANSPARENT);
				if(state & ODS_SELECTED)
					SetTextColor(hdc, m_SelectedTextColor);
				else
					SetTextColor(hdc, m_TextColor);

				// Get Button Text
				size_t size = getTextLength();
				WCHAR* buffer = new WCHAR[size + 1];
				getText(size + 1, buffer);

				// Get Button Text Format
				UINT fmt = 0, fmtH = 0, fmtV = 0;
				LONG style = GetWindowLongPtr(getHandle(), GWL_STYLE);

				// Horizontal Justification
				if(style & BS_LEFT) fmtH = DT_LEFT;
				if(style & BS_RIGHT) fmtH = DT_RIGHT;
				if(style & BS_CENTER) fmtH = DT_CENTER;

				// Vertical Justification
				if(style & BS_TOP) fmtV = DT_TOP;
				if(style & BS_BOTTOM) fmtV = DT_BOTTOM;
				if(style & BS_VCENTER) fmtV = DT_VCENTER;

				fmt = fmtH | fmtV;
				// Multi-line
				if(style & ~BS_MULTILINE) fmt |= DT_SINGLELINE;


				DrawText(hdc, buffer, -1, &rc, fmt);
				delete[] buffer;
				buffer = nullptr;
				return (LRESULT)TRUE;
			}

			LRESULT ButtonControlW::WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
			{
				return DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam);
			}
		}
	}
}

#endif // !BUTTONCONTROL_CPP
