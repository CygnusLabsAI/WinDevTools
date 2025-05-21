#pragma once

#ifndef EDITCONTROL_H
#define EDITCONTROL_H

#include "AControlWindow.h"

namespace WinDevTools {

	namespace GUI {

		namespace Control {

			class EditControlW: public AControlWindowW
			{
				public:
					EditControlW(void);
					const HWND create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle, DWORD _dwExStyle, LPCWSTR _lpszWindowName);
					const HWND create(HWND _hWndParent, int _iX, int _iY, HMENU _hID, DWORD _dwStyle = 0, DWORD _dwExStyle = 0);
					const HWND create(HWND _hWndParent, int _iX, int _iY, int _iWidth, int _iHeight, HMENU _hID, DWORD _dwStyle = 0, DWORD _dwExStyle = 0);

					//const HWND create(HWND _hWndParent, int _iX, int _iY, int _iWidth = 100, int _iHeight = 20, DWORD _dwStyle = WS_CHILD | WS_VISIBLE, DWORD _dwExStyle = 0, LPCWSTR _lpszWindowName = L"");

					// Style Modification Methods
					void setLowercase(bool _bValue);
					void setNumber(bool _bValue);
					void setOEMConvert(bool _bValue);					
					void setUppercase(bool _bValue);
					void setWantReturn(bool _bValue);

					// Control Message Functions

					bool canUndo(void);
					COORD charFromPos(int _iX, int _iY);
					void emptyUndoBuffer(void);
					bool fmtLines(bool _bValue);
					int getFirstVisibleLine(void);
					LPCWSTR getBufferHandle(void);
					UINT getIMEStatus(void);
					UINT getLimitText(void);
					template<size_t SIZE> UINT getLine(UINT _uiIndex, WCHAR (&_pwcBuffer)[SIZE]);
					UINT getLine(UINT _uiIndex, std::wstring& _sBuffer);
					UINT getLineCount(void);
					void getMargins(UINT& _uiLeft, UINT& _uiRight);
					bool getModify(void);
					WCHAR getPasswordChar(void);
					RECT getRect(void);
					void getSel(DWORD& _dwStart, DWORD& _dwEnd);
					LRESULT getThumb(void);	// Further Testing Required
					EDITWORDBREAKPROC getWordBreakProc(void);
					void limitText(UINT _uiLimit);
					UINT lineFromChar(UINT _uiCharIndex);
					int lineIndex(int _iLineIndex);
					UINT lineLength(UINT _uiCharIndex);
					bool lineScroll(int _iHorz, int _iVert);
					COORD posFromChar(UINT _uiCharIndex);
					void replaceSel(bool _bCanUndo, LPCWSTR _szReplace);
					LRESULT scroll(UINT _uiSBAction);
					void scrollCaret(void);
					void setBufferHandle(LPWSTR _szBuffer);
					UINT setIMEStatus(UINT _uiIMEFlags);
					void setLimitText(UINT _uiLimit);
					void setMargins(WORD _uiMarginFlags = EC_LEFTMARGIN | EC_RIGHTMARGIN, WORD _uiLeft = EC_USEFONTINFO, WORD _uiRight = EC_USEFONTINFO);
					void setModify(bool _bValue);
					void setPasswordChar(wchar_t _wcPWChar);
					void setReadOnly(bool _bValue);
					void setRect(LPRECT _lpRect);
					void setRectNP(LPRECT _lpRect);
					bool setTabStops(UINT _uiNumTabStops, PUINT _puiTabStops, bool _bInvalidate = false);
					void setWordBreakProc(EDITWORDBREAKPROC _EditWordBreakProc);
					void undo(void);

					// WM_CTLCOLOREDIT Handler
					virtual LRESULT handleCTLCOLOREDIT(WPARAM _wParam) override;

				private:
					virtual LRESULT WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam) override;

			};
		}
	}
}

#ifdef _UNICODE
	#define EditControl EditControlW
#else
	#define EditControl
#endif // _UNICODE

#ifndef EDITCONTROL_CPP
	#include "EditControl.cpp"
#endif // !EDITCONTROL_CPP

#endif // !EDITCONTROL_H
