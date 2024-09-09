// lab_1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "lab_1.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND Button1;
HWND Button2;
HWND TextEdit;
HWND TextStatic;

static int yShift = 0;
static int xShift = 0;
static int WndWidth = 800;
static int WndHeight = 700;
const static int WndX = 100;
const static int WndY = 10;
const static int BtnWidth = 100;
const static int BtnHeight = 30;
const static int EditWidth = 200;
const static int EditHeight = 30;
const static int Button1Id = 1000;
const static int Button2Id = 1001;
const static int TimerId = 1002;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    NewWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_LAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1));

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
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = NewWndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


void WDrawEllipse(HWND hWnd) {
    HRGN cutRgn, outRgn;
    RECT WRect;
    GetWindowRect(hWnd, &WRect);
    WndWidth = WRect.right - WRect.left; // новая ширина окна
    WndHeight = WRect.bottom - WRect.top; // новая высота окна
    outRgn = CreateEllipticRgn(-10, -WndHeight, WndWidth + 10, WndHeight);
    int r = 80; // радиус вырезанного круга
    cutRgn = CreateEllipticRgn(WndWidth / 2 - r, WndHeight - 200 - r, WndWidth / 2 + r, WndHeight - 200 + r);
    CombineRgn(cutRgn, cutRgn, outRgn, RGN_XOR);
    SetWindowRgn(hWnd, cutRgn, true);
}

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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, WndWidth, CW_USEDEFAULT, WndHeight, nullptr, nullptr, hInstance, nullptr);
    
   MoveWindow(hWnd, WndX, WndY, WndWidth, WndHeight, true);
   //SetWindowPos(hWnd, HWND_TOPMOST, WndX, WndY, WndWidth, WndHeight, SWP_SHOWWINDOW);

   WDrawEllipse(hWnd);

   Button1 = CreateWindow(
       L"BUTTON",  // Predefined class; Unicode assumed 
       L"BUTTON1",      // Button text 
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
       WndX + 20,         // x position 
       WndY + 10,         // y position 
       BtnWidth,        // Button width
       BtnHeight,        // Button height
       hWnd,     // Parent window
       NULL,       // No menu.
       hInstance,
       NULL);      // Pointer not needed.

   Button2 = CreateWindow(
       L"BUTTON",  // Predefined class; Unicode assumed 
       L"BUTTON2",      // Button text 
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
       WndX + 20,         // x position 
       WndY + 50,         // y position 
       BtnWidth,        // Button width
       BtnHeight,        // Button height
       hWnd,     // Parent window
       NULL,       // No menu.
       hInstance,
       NULL);      // Pointer not needed.

   TextEdit = CreateWindow(
       L"EDIT",  // Predefined class; Unicode assumed 
       L"MPEI",      // Button text 
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_BORDER,  // Styles 
       WndX + 20,         // x position 
       WndY + 100,         // y position 
       EditWidth,        // Button width
       EditHeight,        // Button height
       hWnd,     // Parent window
       NULL,       // No menu.
       hInstance,
       NULL);      // Pointer not needed.

   TextStatic = CreateWindow(
       L"STATIC",  // Predefined class; Unicode assumed 
       L"SOME TEXT",      // Button text 
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_BORDER,  // Styles 
       WndX + 20,         // x position 
       WndY + 150,         // y position 
       EditWidth,        // Button width
       EditHeight,        // Button height
       hWnd,     // Parent window
       NULL,       // No menu.
       hInstance,
       NULL);      // Pointer not needed.




   if (Button1 != NULL) {
       SetWindowLong(Button1, GWL_ID, Button1Id);
   }
   if (Button2 != NULL) {
       SetWindowLong(Button2, GWL_ID, Button2Id);
   }

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);


   return TRUE;
}

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
LRESULT CALLBACK NewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
            MessageBox(hWnd, L"The window is created!", L"MESSAGE", MB_OK);
            /*MoveWindow(hWnd, 300, 300, WndWidth, WndHeight, true);*/
        }
        break;
    case WM_LBUTTONDOWN:
        MessageBox(hWnd, L"Left mouse button clicked!", L"MESSAGE", MB_OK);
        break;
    case WM_RBUTTONDOWN:
        MessageBox(hWnd, L"Right mouse button clicked!", L"MESSAGE", MB_OK);
        KillTimer(hWnd, TimerId);
        if (GetParent(Button1) != hWnd) {
            SetParent(Button1, hWnd);
            MoveWindow(Button1, WndX + 20, WndY + 10, BtnWidth, BtnHeight, true);
        }
        break;
    case WM_TIMER:
    {
        xShift+=2;
        yShift += 1;
        MoveWindow(Button1, xShift, yShift, BtnWidth, BtnHeight, true);
        SetWindowPos(Button1, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    case WM_COMMAND:
        {
            char textFromEdit[50];
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
                case IDM_ABOUT:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case IDM_CHANGEPARENT:
                {
                    MessageBox(hWnd, L"Change parent click!", L"MESSAGE", MB_OK);
                    yShift = 0;
                    xShift = 0;
                    SetTimer(hWnd, TimerId, 50, (TIMERPROC)NULL);
                    if (GetParent(Button1) == hWnd) {
                        SetParent(Button1, NULL);
                    }
                    else {
                        KillTimer(hWnd, TimerId);
                        SetParent(Button1, hWnd);
                        MoveWindow(Button1, WndX + 20, WndY + 10, BtnWidth, BtnHeight, true);
                    }
                }
                break;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;
                case Button1Id:
                {
                    TCHAR TextFromEdit[MAX_LOADSTRING];
                    GetWindowText(TextEdit, TextFromEdit, MAX_LOADSTRING);
                    SetWindowText(TextStatic, TextFromEdit);
                }
                break;
                case Button2Id:
                {
                    TCHAR TextFromStatic[MAX_LOADSTRING];
                    GetWindowText(hWnd, TextFromStatic, MAX_LOADSTRING);
                    SetWindowText(TextStatic, TextFromStatic);
                }
                break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        MessageBox(hWnd, L"The window is destroyed!", L"MESSAGE", MB_OK);
        PostQuitMessage(0);
        break;
    case WM_CLOSE:
        MessageBox(hWnd, L"The window is closed", L"MESSAGE", MB_OK);
        DestroyWindow(hWnd);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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
