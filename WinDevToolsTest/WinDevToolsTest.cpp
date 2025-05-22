// WinDevToolsTest.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WinDevToolsTest.h"
#include "Controls/EditControl.h"
#include "Controls/StaticControl.h"
#include "Controls/ButtonControl.h"

using namespace WinDevTools::GUI;



#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

Control::EditControl EditCtrl;
Control::StaticControlW StaticCtrl;
Control::ButtonControl ButtonCtrl;
// Forward declarations of functions included in this code module:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

/** The above functions are handled by AWindow **/

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

uint8_t dummy = 0;
bool goUp = false;

HBITMAP hBitmap;
HICON hIcon;
HENHMETAFILE hEnhMetaFile;

class MainWindow: public AWindow
{
    public:
        MainWindow(LPWSTR _szTitle, LPWSTR _szWindowClass):
            AWindow(_szWindowClass,
                    CS_HREDRAW | CS_VREDRAW,
                    LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_WINDEVTOOLSTEST)),
                    MAKEINTRESOURCEW(IDC_WINDEVTOOLSTEST),
                    LoadCursor(nullptr, IDC_ARROW),
                    (HBRUSH)GetStockObject(LTGRAY_BRUSH),
                    LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SMALL)),
                    0, 0),
            m_lpszTitle(_szTitle)

        {

        }

        virtual LRESULT WndProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
        {
            switch(_uiMsg)
            {
                case WM_CREATE:
                    {
                        
                        hIcon = (HICON)LoadImage(NULL, L"icon1.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
                        ButtonCtrl.create(_hWnd, 10, 10, 100, 50, (HMENU)1001, BS_CHECKBOX | BS_PUSHLIKE, NULL, L"Push Me!");
                        ButtonCtrl.setIconImage(hIcon);
                        int debug = 0;
                    }
                    return DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam);
                case WM_TIMER:
                    {
                        //if(goUp)
                        //{
                        //    dummy++;
                        //    if(dummy == 255) goUp = false;
                        //}
                        //else
                        //{
                        //    dummy--;
                        //    if(dummy == 0) goUp = true;
                        //}
                        //EditCtrl.setTextColor(RGB(255, 0 - dummy, 0 - dummy));
                        //EditCtrl.setBGColor(RGB(dummy, dummy, dummy));
                        //RedrawWindow(EditCtrl.getHandle(), NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
                        std::wstring replace = L"[REPLACE]";
                        EditCtrl.replaceSel(false, replace.c_str());
                        int debug = 0;
                    }
                    break;
                case WM_CTLCOLOREDIT:   // Use case for control window map...predefine in AWindowW/AWindowA class non-static WndProc
                    {
                        if((HWND)_lParam == EditCtrl.getHandle())
                            return EditCtrl.handleCTLCOLOREDIT(_wParam);
                    }
                    break;
                case WM_CTLCOLORSTATIC:
                    {
                        if((HWND)_lParam == StaticCtrl.getHandle())
                            return StaticCtrl.handleCTLCOLORSTATIC(_wParam);
                    }
                    break;
                case WM_COMMAND:
                    {
                        int wmId = LOWORD(_wParam);
                        // Parse the menu selections:
                        switch(wmId)
                        {
                            case 1001:
                                {
                                    int notification = HIWORD(_wParam);
                                    int debug = 0;
                                }
                                break;
                            case IDM_ABOUT:
                                DialogBox(getInstance(), MAKEINTRESOURCE(IDD_ABOUTBOX), _hWnd, About);
                                break;
                            case IDM_EXIT:
                                DestroyWindow(_hWnd);
                                break;
                            default:
                                return DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam);
                        }
                    }
                    break;
                case WM_PAINT:
                    {
                        PAINTSTRUCT ps;
                        HDC hdc = BeginPaint(_hWnd, &ps);
                        // TODO: Add any drawing code that uses hdc here...
                        EndPaint(_hWnd, &ps);
                    }
                    break;
                case WM_DESTROY:
                    PostQuitMessage(0);
                    break;
                default:
                    return DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam);
            }
            return 0;
        }
    private:
        LPWSTR m_lpszTitle;
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDEVTOOLSTEST, szWindowClass, MAX_LOADSTRING);
    //MyRegisterClass(hInstance);
    MainWindow mainWnd(szTitle, szWindowClass);

    // Perform application initialization:
    //if (!InitInstance (hInstance, nCmdShow))
    //{
    //    return FALSE;
    //}
    mainWnd.create(CW_USEDEFAULT, 0, szTitle);
    mainWnd.show();
    mainWnd.update();

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDEVTOOLSTEST));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
/** Handled by MainWindow and inherited AWindow Constructors **/
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//    WNDCLASSEXW wcex;
//
//    wcex.cbSize = sizeof(WNDCLASSEX);
//
//    wcex.style          = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc    = WndProc;
//    wcex.cbClsExtra     = 0;
//    wcex.cbWndExtra     = 0;
//    wcex.hInstance      = hInstance;
//    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDEVTOOLSTEST));
//    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
//    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDEVTOOLSTEST);
//    wcex.lpszClassName  = szWindowClass;
//    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//    return RegisterClassExW(&wcex);
//}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
/** Handled by MainWindow inherited create and show and update methods **/
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//   hInst = hInstance; // Store instance handle in our global variable
//
//   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//   if (!hWnd)
//   {
//      return FALSE;
//   }
//
//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);
//
//   return TRUE;
//}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
/** Handled by MainWindow WndProc method **/
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message)
//    {
//    case WM_COMMAND:
//        {
//            int wmId = LOWORD(wParam);
//            // Parse the menu selections:
//            switch (wmId)
//            {
//            case IDM_ABOUT:
//                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//                break;
//            case IDM_EXIT:
//                DestroyWindow(hWnd);
//                break;
//            default:
//                return DefWindowProc(hWnd, message, wParam, lParam);
//            }
//        }
//        break;
//    case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hWnd, &ps);
//            // TODO: Add any drawing code that uses hdc here...
//            EndPaint(hWnd, &ps);
//        }
//        break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
