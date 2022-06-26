// AnalogClock.cpp : 定義應用程式的進入點。
//

#include "framework.h"
#include "AnalogClock.h"
#include <time.h>
#include <math.h>

#define MAX_LOADSTRING 100
#define PI 3.1415926
// 全域變數:
HINSTANCE hInst;                                // 目前執行個體
WCHAR szTitle[MAX_LOADSTRING];                  // 標題列文字
WCHAR szWindowClass[MAX_LOADSTRING];            // 主視窗類別名稱

// 這個程式碼模組所包含之函式的向前宣告:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置程式碼。

    // 將全域字串初始化
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ANALOGCLOCK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 執行應用程式初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ANALOGCLOCK));

    MSG msg;

    // 主訊息迴圈:
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
//  函式: MyRegisterClass()
//
//  用途: 註冊視窗類別。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ANALOGCLOCK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ANALOGCLOCK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函式: InitInstance(HINSTANCE, int)
//
//   用途: 儲存執行個體控制代碼並且建立主視窗
//
//   註解:
//
//        在這個函式中，我們將執行個體控制代碼儲存在全域變數中，
//        並建立及顯示主程式視窗。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 將執行個體控制代碼儲存在全域變數中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函式: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  用途: 處理主視窗的訊息。
//
//  WM_COMMAND  - 處理應用程式功能表
//  WM_PAINT    - 繪製主視窗
//  WM_DESTROY  - 張貼結束訊息然後傳回
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 9999, 1000, NULL);
        break;
    case WM_TIMER:
        if (wParam == 9999)
            InvalidateRect(hWnd, NULL, true);
        break;
    case WM_SIZE:
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 剖析功能表選取項目:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
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
        HBRUSH hBrush;
        HPEN hPen;
        RECT clientRect;
        SYSTEMTIME x;
        float sita = 0;
        double xline, yline;
        double clock, sec, min, hour;
        double temHour, temMin, ptLong, xBegin, xEnd, yBegin, yEnd;
        GetClientRect(hWnd, &clientRect);

        hPen = CreatePen(PS_SOLID, 14, RGB(153,107, 31));
        hBrush = CreateSolidBrush(RGB(255, 228, 181));
        SelectObject(hdc, hPen);
        SelectObject(hdc, hBrush);
        xline = (clientRect.left + clientRect.right) / 2;/*原點*/
        yline = (clientRect.bottom + clientRect.top) / 2;
        clock = min(xline, yline) * 4 / 5;
        sec = clock * 6 / 7;
        min = clock * 5 / 6;
        hour = clock * 2 / 3;
        /*畫時鐘的部分*/
        Ellipse(hdc, int(xline - clock), int(yline - clock), int(xline + clock), int(yline + clock));
        for (int i = 0; i < 60; i++) /*刻度*/
        {
            if (i % 5)
            {
                hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));/*小刻度*/
                ptLong = clock * 9 / 10;
            }
            else
            {
                hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));/*大刻度*/
                ptLong = clock * 7 / 8;
            }
            SelectObject(hdc, hPen);

            xBegin = xline + clock * sin(2 * PI * i / 60);
            yBegin = yline + clock * cos(2 * PI * i / 60);
            xEnd = xline + ptLong * sin(2 * PI * i / 60);
            yEnd = yline + ptLong * cos(2 * PI * i / 60);

            MoveToEx(hdc, (int)xBegin, (int)yBegin, NULL);
            LineTo(hdc, (int)xEnd, (int)yEnd);
            DeleteObject(hPen);
        }

        GetLocalTime(&x);

        hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));/*秒針*/
        SelectObject(hdc, hPen);

        sita = float(2 * PI * x.wSecond / 60);

        xBegin = xline + (int)(sec * sin(sita));
        yBegin = yline - (int)(sec * cos(sita));
        xEnd = xline + (int)(clock * sin(sita + PI) / 8);
        yEnd = yline - (int)(clock * cos(sita + PI) / 8);

        MoveToEx(hdc, (int)xBegin, (int)yBegin, NULL);
        LineTo(hdc, (int)xEnd, (int)yEnd);

        hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));/*分針*/
        SelectObject(hdc, hPen);
        temMin = (double)(x.wSecond) / 60;
        temHour = x.wMinute + temMin;
        sita = float(2 * PI * temHour/60);
        //sita = float(2 * PI * x.wMinute / 60);

        xBegin = xline + (int)(min * sin(sita));
        yBegin = yline - (int)(min * cos(sita));
        xEnd = xline + (int)(clock * sin(sita + PI) / 8);
        yEnd = yline - (int)(clock * cos(sita + PI) / 8);

        MoveToEx(hdc, (int)xBegin, (int)yBegin, NULL);
        LineTo(hdc, (int)xEnd, (int)yEnd);

        hPen = CreatePen(PS_SOLID, 10, RGB(0, 0, 0));/*時針*/
        SelectObject(hdc, hPen);

        temMin = (double)(x.wMinute) / 60;
        temHour = x.wHour + temMin;    
        sita = float(2 * PI * temHour / 12);

        xBegin = xline + (double)(hour * sin(sita));
        yBegin = yline - (double)(hour * cos(sita));
        xEnd = xline + (double)(clock * sin(sita + PI) / 8);
        yEnd = yline - (double)(clock * cos(sita + PI) / 8);

        MoveToEx(hdc, (int)xBegin, (int)yBegin, NULL);
        LineTo(hdc, (int)xEnd, (int)yEnd);

        DeleteObject(hPen);
        DeleteObject(hBrush);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// [關於] 方塊的訊息處理常式。
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
