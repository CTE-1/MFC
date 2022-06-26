// DrawShapeHomework.cpp : 定義應用程式的進入點。
//

#include "framework.h"
#include "DrawShapeHomework.h"
#include <commdlg.h>

#define MAX_LOADSTRING 100

// 圖形代碼
#define SHAPE_LINE      0
#define SHAPE_RECT      1
#define SHAPE_ELIIPSE   2
#define SHAPE_TRIANGLE   3
#define SHAPE_TRAPEZOID  4
#define SHAPE_PARALLELOGRAM  5
#define SHAPE_DIAMOND  6
#define SHAPE_HOURGLASS 7
int nShape = SHAPE_LINE;                    // 選擇繪製之圖形(預設為直線)
int nLineWidth = 1;                         // 預設線寬為1                         
COLORREF colorLine = RGB(0, 0, 0);            // 預設線條為黑色           
COLORREF colorBrush = RGB(255, 255, 255);   // 預設筆刷為白色
BOOL bHasLine = TRUE;                       // 預設有線條
BOOL bHasBrush = TRUE;                      // 預設有填充色
POINT pt1, pt2;
void DrawShape(HDC hdc);                    // 根據屬性繪製圖形
COLORREF ChooseBrushColor(HWND hWNd);
COLORREF ChooseLineColor(HWND hWNd);
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
    LoadStringW(hInstance, IDC_DRAWSHAPEHOMEWORK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 執行應用程式初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAWSHAPEHOMEWORK));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAWSHAPEHOMEWORK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DRAWSHAPEHOMEWORK);
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
            case IDM_TOOL_LINE:
            case IDM_TOOL_RECT:
            case IDM_TOOL_ELLIPSE:
            case IDM_TOOL_TRIANGLE:
            case IDM_TOOL_TRAPEZOID:
            case IDM_TOOL_PARALLELOGRAM:
            case IDM_TOOL_DIAMOND:
            case IDM_TOOL_HOURGLASS:
                nShape = wmId - IDM_TOOL_LINE;  
                break;

            case IDM_TOOL_NULL_LINE:
                bHasLine = FALSE;               
                break;
            case IDM_TOOL_RED_LINE:
                colorLine = RGB(255, 0, 0);     
                break;
            case IDM_TOOL_GREEN_LINE:
                colorLine = RGB(0, 255, 0);     
                break;
            case IDM_TOOL_BLUE_LINE:
                colorLine = RGB(0, 0, 255);     
                break;
            case IDM_TOOL_BLACK_LINE:
                colorLine = RGB(0, 0, 0);       
                break;

            case IDM_TOOL_LINE_1:
                bHasLine = TRUE;
                nLineWidth = 1;                 
                break;
            case IDM_TOOL_LINE_2:
                bHasLine = TRUE;
                nLineWidth = 2;                
                break;
            case IDM_TOOL_LINE_4:
                bHasLine = TRUE;
                nLineWidth = 4;                 
                break;
            case IDM_TOOL_LINE_8:
                bHasLine = TRUE;
                nLineWidth = 8;                 
                break;
            case IDM_TOOL_NULL_BRUSH:
                bHasBrush = FALSE;             
                break;
            case IDM_TOOL_CHOOSE_COLOR:
                bHasBrush = TRUE;
                colorBrush = ChooseBrushColor(hWnd);    
                break;
            case IDM_TOOL_CHOOSE_LINE_COLOR:
                colorLine = ChooseLineColor(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_CREATE:
        {
            RECT rect;
            GetClientRect(hWnd, &rect);
            pt1.x = pt1.y = 10;
            pt2.x = rect.right - 10; pt2.y = rect.bottom - 10;
            break;
        }
    case WM_LBUTTONDOWN:
        pt1.x = pt2.x = LOWORD(lParam);
        pt1.y = pt2.y = HIWORD(lParam);
        SetCapture(hWnd);                           
        break;
    case WM_MOUSEMOVE:
    {
        HWND hCap = GetCapture();               
        if (hCap != hWnd) break;                

        HDC hdc = GetDC(hWnd);                 

        HGDIOBJ hPen = GetStockObject(WHITE_PEN);       
        HGDIOBJ hBrush = GetStockObject(NULL_BRUSH);    

        HGDIOBJ hOldPen = SelectObject(hdc, hPen);     
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);  

        SetROP2(hdc, R2_XORPEN);                

        DrawShape(hdc);                         

        pt2.x = LOWORD(lParam);
        pt2.y = HIWORD(lParam);

        DrawShape(hdc);                        

        ReleaseDC(hWnd, hdc);                  
        break;
    }
    case WM_LBUTTONUP:
    {
        HWND hCap = GetCapture();               
        if (hCap != hWnd) break;                
        ReleaseCapture();                       
        InvalidateRect(hWnd, NULL, TRUE);       
        
    }break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            HPEN hPen;
            hPen = bHasLine ? CreatePen(PS_SOLID, nLineWidth, colorLine)
                : (HPEN)GetStockObject(NULL_PEN);
            HBRUSH hBrush;
            hBrush = bHasBrush ? CreateSolidBrush(colorBrush)
                : (HBRUSH)GetStockObject(NULL_BRUSH);

            HGDIOBJ hOldPen = SelectObject(hdc, hPen);
            HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);

            DrawShape(hdc);

            SelectObject(hdc, hOldPen);
            SelectObject(hdc, hOldBrush);

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
COLORREF ChooseBrushColor(HWND hWnd)
{
    CHOOSECOLOR cc;                         // 顏色選取結構 

    static COLORREF colorCust[] = {          // 用戶自訂色彩16色
        RGB(0, 5, 5),  RGB(0, 15, 55), RGB(0, 25, 155), RGB(0, 35, 255),
        RGB(10, 0, 5), RGB(10, 20, 55), RGB(10, 40, 155), RGB(10, 60, 255),
        RGB(100, 5, 5), RGB(100, 25, 55), RGB(100,  50, 155), RGB(100, 125, 255),
        RGB(200, 120, 5), RGB(200, 150,  55), RGB(200, 200, 155), RGB(200, 250, 255)
    };

    COLORREF rgbCurrent = colorBrush;       // 目前選擇顏色

    // 設定CHOOSECOLOR結構
    ZeroMemory(&cc, sizeof(cc));
    cc.lStructSize = sizeof(cc);
    cc.hwndOwner = hWnd;                    // 對話盒擁有者
    cc.rgbResult = colorBrush;              // 現在使用的繪圖刷顏色
    cc.lpCustColors = (LPDWORD)colorCust;  // 用戶自訂色彩陣列指標
    cc.Flags = CC_FULLOPEN | CC_RGBINIT;    // 開啟方式

    if (ChooseColor(&cc) == TRUE)           // 開啟顏色選取對話盒
        rgbCurrent = cc.rgbResult;          // <確定>之顏色

    return rgbCurrent;                      // 回傳繪圖刷顏色
}

COLORREF ChooseLineColor(HWND hWnd)
{
    CHOOSECOLOR cc;                         // 顏色選取結構 

    static COLORREF colorCust[] = {          // 用戶自訂色彩16色
        RGB(0, 5, 5),  RGB(0, 15, 55), RGB(0, 25, 155), RGB(0, 35, 255),
        RGB(10, 0, 5), RGB(10, 20, 55), RGB(10, 40, 155), RGB(10, 60, 255),
        RGB(100, 5, 5), RGB(100, 25, 55), RGB(100,  50, 155), RGB(100, 125, 255),
        RGB(200, 120, 5), RGB(200, 150,  55), RGB(200, 200, 155), RGB(200, 250, 255)
    };

    COLORREF rgbCurrent = colorLine;       // 目前選擇顏色

    // 設定CHOOSECOLOR結構
    ZeroMemory(&cc, sizeof(cc));
    cc.lStructSize = sizeof(cc);
    cc.hwndOwner = hWnd;                    // 對話盒擁有者
    cc.rgbResult = colorLine;              // 現在使用的繪圖刷顏色
    cc.lpCustColors = (LPDWORD)colorCust;  // 用戶自訂色彩陣列指標
    cc.Flags = CC_FULLOPEN | CC_RGBINIT;    // 開啟方式

    if (ChooseColor(&cc) == TRUE)           // 開啟顏色選取對話盒
        rgbCurrent = cc.rgbResult;          // <確定>之顏色

    return rgbCurrent;                      // 回傳繪圖刷顏色
}

void DrawShape(HDC hdc)
{
    if (nShape == SHAPE_LINE) {
        MoveToEx(hdc, pt1.x, pt1.y, NULL);
        LineTo(hdc, pt2.x, pt2.y);
    }
    else if (nShape == SHAPE_RECT) {
        Rectangle(hdc, pt1.x, pt1.y, pt2.x, pt2.y);
    }
    else if (nShape == SHAPE_ELIIPSE) {
        Ellipse(hdc, pt1.x, pt1.y, pt2.x, pt2.y);
    }
    else if (nShape == SHAPE_TRIANGLE) {
        POINT vertices[] = { {(pt1.x+pt2.x)/2, pt1.y}, {pt2.x, pt2.y}, {pt1.x, pt2.y} };
        Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
    }
    else if (nShape == SHAPE_TRAPEZOID) {
        POINT vertices[] = { {(pt1.x+(pt1.x + pt2.x) / 2)/2, pt1.y}, {(pt2.x + (pt1.x + pt2.x) / 2) / 2, pt1.y}, {pt2.x, pt2.y}, {pt1.x, pt2.y} };
        Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
    }
    else if (nShape == SHAPE_PARALLELOGRAM) {
        POINT vertices[] = { {(pt1.x + (pt1.x + pt2.x) / 2) / 2, pt1.y}, {(((pt1.x + (pt1.x + pt2.x) / 2) / 2)-pt1.x)+pt2.x, pt1.y}, {pt2.x, pt2.y}, {pt1.x, pt2.y} };
        Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
    }
    else if (nShape == SHAPE_DIAMOND) {
        POINT vertices[] = { {(pt1.x + pt2.x) / 2, pt1.y}, {pt2.x, (pt1.y + pt2.y) / 2}, {(pt1.x + pt2.x) / 2, pt2.y}, {pt1.x, (pt1.y + pt2.y) / 2} };
        Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
    }
    else if (nShape == SHAPE_HOURGLASS) {
        POINT vertices[] = { {pt1.x, pt1.y}, {pt2.x, pt1.y}, {(pt1.x + pt2.x) / 2,(pt1.y+ pt2.y) / 2}, {pt1.x, pt2.y}, {pt2.x, pt2.y} };
        Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
    }
}