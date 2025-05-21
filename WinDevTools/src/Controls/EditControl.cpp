#ifndef EDITCONTROL_CPP
#define EDITCONTROL_CPP

#include "EditControl.h"

namespace WinDevTools {

	namespace GUI {

		namespace Control {

			EditControlW::EditControlW(void):
				AControlWindowW(L"EDIT")
			{
				m_TextColor = RGB(0, 0, 0);
				m_BkColor = RGB(255, 255, 255);
			}

			const HWND EditControlW::create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle, LPCWSTR _lpszWindowName)
			{
				HDC hDCParent = GetDC(_hWndParent);
				m_TextColor = GetTextColor(hDCParent);
				m_BkColor = GetBkColor(hDCParent);
				ReleaseDC(_hWndParent, hDCParent);
				return AControlWindowW::create(_hWndParent, _iWidth, _iHeight, _lpszWindowName, _iX, _iY, _dwStyle | WS_VISIBLE | WS_BORDER, _dwExStyle, _hID);
			}

			const HWND EditControlW::create(HWND _hWndParent, int _iX, int _iY, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle)
			{
				return create(_hWndParent, _iX, _iY, 100, 20, _hID, _dwStyle, _dwExStyle, L"");
			}

			const HWND EditControlW::create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle)
			{
				return create(_hWndParent, _iX, _iY, _iWidth, _iHeight, _hID, _dwStyle, _dwExStyle, L"");
			}

			void EditControlW::setLowercase(bool _bValue)
			{
				HWND hWnd = getHandle();
				LONG style = GetWindowLong(hWnd, GWL_STYLE);
				if(_bValue) SetWindowLong(hWnd, GWL_STYLE, style | ES_LOWERCASE);
				else SetWindowLong(hWnd, GWL_STYLE, style & ~ES_LOWERCASE);
			}

			void EditControlW::setNumber(bool _bValue)
			{
				HWND hWnd = getHandle();
				LONG style = GetWindowLong(hWnd, GWL_STYLE);
				if(_bValue) SetWindowLong(hWnd, GWL_STYLE, style | ES_NUMBER);
				else SetWindowLong(hWnd, GWL_STYLE, style & ~ES_NUMBER);
			}

			void EditControlW::setOEMConvert(bool _bValue)
			{
				HWND hWnd = getHandle();
				LONG style = GetWindowLong(hWnd, GWL_STYLE);
				if(_bValue) SetWindowLong(hWnd, GWL_STYLE, style | ES_OEMCONVERT);
				else SetWindowLong(hWnd, GWL_STYLE, style & ~ES_OEMCONVERT);
			}

			void EditControlW::setUppercase(bool _bValue)
			{
				HWND hWnd = getHandle();
				LONG style = GetWindowLong(hWnd, GWL_STYLE);
				if(_bValue) SetWindowLong(hWnd, GWL_STYLE, style | ES_UPPERCASE);
				else SetWindowLong(hWnd, GWL_STYLE, style & ~ES_UPPERCASE);
			}

			void EditControlW::setWantReturn(bool _bValue)
			{
				HWND hWnd = getHandle();
				LONG style = GetWindowLong(hWnd, GWL_STYLE);
				if(_bValue) SetWindowLong(hWnd, GWL_STYLE, style | ES_WANTRETURN);
				else SetWindowLong(hWnd, GWL_STYLE, style & ~ES_WANTRETURN);
			}

			bool EditControlW::canUndo(void)
			{
				return SendMessage(getHandle(), EM_CANUNDO, NULL, NULL);
			}

			COORD EditControlW::charFromPos(int _iX, int _iY)
			{
				LRESULT result = SendMessage(getHandle(), EM_CHARFROMPOS, NULL, MAKELPARAM(_iX, _iY));
				COORD coords;
				coords.X = LOWORD(result);
				coords.Y = HIWORD(result);
				return coords;
			}

			void EditControlW::emptyUndoBuffer(void)
			{
				SendMessage(getHandle(), EM_EMPTYUNDOBUFFER, NULL, NULL);
			}

			bool EditControlW::fmtLines(bool _bValue)
			{
				return SendMessage(getHandle(), EM_FMTLINES, (WPARAM)_bValue, NULL);
			}

			int EditControlW::getFirstVisibleLine(void)
			{
				return SendMessage(getHandle(), EM_GETFIRSTVISIBLELINE, NULL, NULL);
			}

			LPCWSTR EditControlW::getBufferHandle(void)
			{
				LRESULT result = SendMessage(getHandle(), EM_GETHANDLE, NULL, NULL);
				LPCWSTR ret = (LPCWSTR)LocalLock((HLOCAL)result);
				LocalUnlock((HLOCAL)result);
				return ret;
			}

			UINT EditControlW::getIMEStatus(void)
			{
				return (UINT)SendMessage(getHandle(), EM_GETIMESTATUS, EMSIS_COMPOSITIONSTRING, NULL);
			}

			UINT EditControlW::getLimitText(void)
			{
				return (UINT)SendMessage(getHandle(), EM_GETLIMITTEXT, NULL, NULL);
			}

			template<size_t SIZE> UINT EditControlW::getLine(UINT _uiIndex, WCHAR (&_pwcBuffer)[SIZE])
			{
				TCHAR size = (TCHAR)(sizeof(_pwcBuffer) / sizeof(_pwcBuffer[0]));
				_pwcBuffer[0] = size;
				return SendMessage(getHandle(), EM_GETLINE, _uiIndex, (LPARAM)&_pwcBuffer[0]);
			}

			UINT EditControlW::getLine(UINT _uiIndex, std::wstring& _sBuffer)
			{
				TCHAR size = (TCHAR)(_sBuffer.size());
				_sBuffer[0] = size;
				return SendMessage(getHandle(), EM_GETLINE, _uiIndex, (LPARAM)&_sBuffer[0]);
			}

			UINT EditControlW::getLineCount(void)
			{
				return SendMessage(getHandle(), EM_GETLINECOUNT, NULL, NULL);
			}

			void EditControlW::getMargins(UINT& _uiLeft, UINT& _uiRight)
			{
				LRESULT result = SendMessage(getHandle(), EM_GETMARGINS, NULL, NULL);
				_uiLeft = LOWORD(result);
				_uiRight = HIWORD(result);
			}

			bool EditControlW::getModify(void)
			{
				return SendMessage(getHandle(), EM_GETMODIFY, NULL, NULL);
			}

			WCHAR EditControlW::getPasswordChar(void)
			{
				return (WCHAR)SendMessage(getHandle(), EM_GETPASSWORDCHAR, NULL, NULL);
			}

			RECT EditControlW::getRect(void)
			{
				RECT rect;
				SendMessage(getHandle(), EM_GETRECT, NULL, (LPARAM)&rect);
				return rect;
			}

			void EditControlW::getSel(DWORD& _dwStart, DWORD& _dwEnd)
			{
				SendMessage(getHandle(), EM_GETSEL, (WPARAM)&_dwStart, (LPARAM)&_dwEnd);
			}

			LRESULT EditControlW::getThumb(void)
			{
				return SendMessage(getHandle(), EM_GETTHUMB, NULL, NULL);
			}

			EDITWORDBREAKPROC EditControlW::getWordBreakProc(void)
			{
				return (EDITWORDBREAKPROC)SendMessage(getHandle(), EM_GETWORDBREAKPROC, NULL, NULL);
			}

			void EditControlW::limitText(UINT _uiLimit)
			{
				SendMessage(getHandle(), EM_LIMITTEXT, (WPARAM)_uiLimit, NULL);
			}

			UINT EditControlW::lineFromChar(UINT _uiCharIndex)
			{
				return (UINT)SendMessage(getHandle(), EM_LINEFROMCHAR, (WPARAM)_uiCharIndex, NULL);
			}

			int EditControlW::lineIndex(int _iLineIndex)
			{
				return (int)SendMessage(getHandle(), EM_LINEINDEX, (WPARAM)_iLineIndex, NULL);
			}

			UINT EditControlW::lineLength(UINT _uiCharIndex)
			{
				return (UINT)SendMessage(getHandle(), EM_LINELENGTH, (WPARAM)_uiCharIndex, NULL);
			}

			bool EditControlW::lineScroll(int _iHorz, int _iVert)
			{
				return SendMessage(getHandle(), EM_LINESCROLL, (WPARAM)_iHorz, (LPARAM)_iVert);
			}

			COORD EditControlW::posFromChar(UINT _uiCharIndex)
			{
				LRESULT result = SendMessage(getHandle(), EM_POSFROMCHAR, (WPARAM)_uiCharIndex, NULL);
				COORD coords;
				coords.X = LOWORD(result);
				coords.Y = HIWORD(result);
				return coords;
			}

			void EditControlW::replaceSel(bool _bCanUndo, LPCWSTR _szReplace)
			{
				SendMessage(getHandle(), EM_REPLACESEL, (WPARAM)_bCanUndo, (LPARAM)_szReplace);
			}

			LRESULT EditControlW::scroll(UINT _uiSBAction)
			{
				return SendMessage(getHandle(), EM_SCROLL, (WPARAM)_uiSBAction, NULL);
			}

			void EditControlW::scrollCaret(void)
			{
				SendMessage(getHandle(), EM_SCROLLCARET, NULL, NULL);
			}

			void EditControlW::setBufferHandle(LPWSTR _szText)
			{
				// Get current buffer handle (if any)
				HLOCAL hOld = (HLOCAL)SendMessage(getHandle(), EM_GETHANDLE, NULL, NULL);

				// Allocate new buffer
				int iStrLen = lstrlen(_szText);
				HLOCAL hNew = LocalAlloc(LMEM_MOVEABLE, iStrLen + 1);
				if(hNew == NULL) return;

				// Copy text to new buffer
				LPWSTR szNewBuffer = (LPWSTR)LocalLock(hNew);
				if(szNewBuffer == NULL) return;
				lstrcpy(szNewBuffer, _szText);
				LocalUnlock(hNew);

				// Set new buffer
				SendMessage(getHandle(), EM_SETHANDLE, (WPARAM)hNew, NULL);

				// Free old buffer (if any)
				if(hOld) LocalFree(hOld);
			}

			UINT EditControlW::setIMEStatus(UINT _uiIMEFlags)
			{
				return (UINT)SendMessage(getHandle(), EM_SETIMESTATUS, EMSIS_COMPOSITIONSTRING, (LPARAM)_uiIMEFlags);
			}

			void EditControlW::setLimitText(UINT _uiLimit)
			{
				SendMessage(getHandle(), EM_SETLIMITTEXT, (WPARAM)_uiLimit, NULL);
			}

			void EditControlW::setMargins(WORD _uiMarginFlags, WORD _uiLeft, WORD _uiRight)
			{
				SendMessage(getHandle(), EM_SETMARGINS, (WPARAM)_uiMarginFlags, MAKELPARAM(_uiLeft, _uiRight));
			}

			void EditControlW::setModify(bool _bValue)
			{
				SendMessage(getHandle(), EM_SETMODIFY, (WPARAM)_bValue, NULL);
			}

			void EditControlW::setPasswordChar(wchar_t _wcPWChar)
			{
				SendMessage(getHandle(), EM_SETPASSWORDCHAR, (WPARAM)_wcPWChar, NULL);
			}

			void EditControlW::setReadOnly(bool _bValue)
			{
				HWND hWnd = getHandle();
				if(_bValue) SendMessage(hWnd, EM_SETREADONLY, TRUE, NULL);
				else SendMessage(hWnd, EM_SETREADONLY, FALSE, NULL);
			}

			void EditControlW::setRect(LPRECT _lpRect)
			{
				SendMessage(getHandle(), EM_SETRECT, NULL, (LPARAM)_lpRect);
			}

			void EditControlW::setRectNP(LPRECT _lpRect)
			{
				SendMessage(getHandle(), EM_SETRECTNP, NULL, (LPARAM)_lpRect);
			}

			bool EditControlW::setTabStops(UINT _uiNumTabStops, PUINT _puiTabStops, bool _bInvalidate)
			{
				if(_bInvalidate)
				{
					bool ret = SendMessage(getHandle(), EM_SETTABSTOPS, (WPARAM)_uiNumTabStops, (LPARAM)_puiTabStops);
					InvalidateRect(getHandle(), NULL, TRUE);
					return ret;
				}
				return SendMessage(getHandle(), EM_SETTABSTOPS, (WPARAM)_uiNumTabStops, (LPARAM)_puiTabStops);
			}

			void EditControlW::setWordBreakProc(EDITWORDBREAKPROC _EditWordBreakProc)
			{
				SendMessage(getHandle(), EM_SETWORDBREAKPROC, NULL, (LPARAM)_EditWordBreakProc);
			}

			void EditControlW::undo(void)
			{
				SendMessage(getHandle(), EM_UNDO, NULL, NULL);
			}

			LRESULT EditControlW::handleCTLCOLOREDIT(WPARAM _wParam)
			{
				SetTextColor((HDC)_wParam, m_TextColor);
				SetBkColor((HDC)_wParam, m_BkColor);
				return (LRESULT)((HBRUSH)GetStockObject(DC_BRUSH));
			}

			LRESULT EditControlW::WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
			{
				return DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam);
			}
		}
	}
}
#endif // !EDITCONTROL_CPP
