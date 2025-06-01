#ifndef SCROLLBARCONTROL_CPP
#define SCROLLBARCONTROL_CPP

#include "ScrollbarControl.h"
#pragma comment(lib, "user32.lib")

namespace WinDevTools {

	namespace GUI {

		namespace Control {

			ScrollbarControlW::ScrollbarControlW(void):
				AControlWindowW(L"SCROLLBAR"),
				m_hBarBrush(NULL)
			{
				
			}

			const HWND ScrollbarControlW::create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle)
			{
				return AControlWindowW::create(_hWndParent, _iWidth, _iHeight, (PTSTR)NULL, _iX, _iY, _dwStyle | WS_VISIBLE, _dwExStyle, _hID);
			}

			const HWND ScrollbarControlW::create(HWND _hWndParent, int _iX, int _iY, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle)
			{
				return create(_hWndParent, _iX, _iY, 100, 20, _hID, _dwStyle, _dwExStyle);
			}

			bool ScrollbarControlW::enableArrows(WORD _wFlag)
			{
				return SendMessage(getHandle(), SBM_ENABLE_ARROWS, (WPARAM)_wFlag, NULL);
			}

			bool ScrollbarControlW::getScrollbarInfo(LPSCROLLBARINFO _lpScrollbarInfo)
			{
				return SendMessage(getHandle(), SBM_GETSCROLLBARINFO, NULL, (LPARAM)_lpScrollbarInfo);
			}

			bool ScrollbarControlW::getScrollInfo(LPSCROLLINFO _lpScrollInfo, WORD _wFlags)
			{
				_lpScrollInfo->cbSize = sizeof(SCROLLINFO);
				_lpScrollInfo->fMask = _wFlags;
				return SendMessage(getHandle(), SBM_GETSCROLLINFO, NULL, (LPARAM)_lpScrollInfo);
			}

			int ScrollbarControlW::setScrollInfo(LPSCROLLINFO _lpScrollInfo, WORD _wFlags, bool _bRedraw)
			{
				_lpScrollInfo->cbSize = sizeof(SCROLLINFO);
				_lpScrollInfo->fMask = _wFlags;
				return SendMessage(getHandle(), SBM_SETSCROLLINFO, (WPARAM)_bRedraw, (LPARAM)_lpScrollInfo);
			}

			int ScrollbarControlW::getPos(void)
			{
				SCROLLINFO si;
				if(getScrollInfo(&si, SIF_POS)) return si.nPos;
				return -1;
			}

			void ScrollbarControlW::setPos(int _iNewPos, bool _bRedraw)
			{
				SendMessage(getHandle(), SBM_SETPOS, (WPARAM)_iNewPos, (LPARAM)_bRedraw);
			}

			void ScrollbarControlW::getRange(int* _piMin, int* _piMax)
			{
				SendMessage(getHandle(), SBM_GETRANGE, (WPARAM)_piMin, (LPARAM)_piMax);
			}

			void ScrollbarControlW::setRange(int _iMin, int _iMax, bool _bRedraw)
			{
				if(_bRedraw) SendMessage(getHandle(), SBM_SETRANGEREDRAW, (WPARAM)_iMin, (LPARAM)_iMax);
				else SendMessage(getHandle(), SBM_SETRANGE, (WPARAM)_iMin, (LPARAM)_iMax);
			}

			int ScrollbarControlW::getPage(void)
			{
				SCROLLINFO si;
				if(getScrollInfo(&si, SIF_PAGE)) return si.nPage;
				return -1;
			}

			void ScrollbarControlW::setPage(int _iPage, bool _bRedraw)
			{
				SCROLLINFO si;
				setScrollInfo(&si, SIF_PAGE, _bRedraw);
			}

			int ScrollbarControlW::getTrackPos(void)
			{
				SCROLLINFO si;
				if(getScrollInfo(&si, SIF_TRACKPOS)) return si.nTrackPos;
				return -1;
			}

			LRESULT ScrollbarControlW::handleCTLCOLORSCROLLBAR(WPARAM _wParam)
			{
				SetBkColor((HDC)_wParam, m_BkColor);

				LOGBRUSH lb;
				if(m_hBarBrush && GetObject(m_hBarBrush, sizeof(LOGBRUSH), &lb) == sizeof(LOGBRUSH))
				{
					if(lb.lbStyle == BS_SOLID)
					{
						if(lb.lbColor != m_BkColor)
						{
							DeleteObject(m_hBarBrush);
							m_hBarBrush = NULL;
						}
					}
				}
				if(!m_hBarBrush) m_hBarBrush = CreateSolidBrush(m_BkColor);
				return (LRESULT)(m_hBarBrush);
			}

			LRESULT ScrollbarControlW::WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
			{
				switch(_uiMsg)
				{
					case WM_HSCROLL:
						break;
				}
				return DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam);
			}

		}
	}
}

#endif // !SCROLLBARCONTROL_CPP
