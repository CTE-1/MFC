// SimpleCalculatorPanel.cpp : 定義應用程式的進入點。
//

#include "framework.h"
#include "SimpleCalculatorPanel.h"

#define MAX_LOADSTRING 100
#define IDC_EDITBOX_TEXT 1000
#define IDC_BUTTON_ONE 1001
#define IDC_BUTTON_TWO  1002
#define IDC_BUTTON_THREE  1003
#define IDC_BUTTON_FOUR  1004
#define IDC_BUTTON_FIVE  1005
#define IDC_BUTTON_SIX 1006
#define IDC_BUTTON_SEVEN  1007
#define IDC_BUTTON_EIGHT  1008
#define IDC_BUTTON_NINE  1009
#define IDC_BUTTON_ZERO  1010
#define IDC_BUTTON_ZEROO  1011
#define IDC_BUTTON_ZEROOO 1012
#define IDC_BUTTON_C 1013
#define IDC_BUTTON_DELETE  1014
#define IDC_BUTTON_N  1015
#define IDC_BUTTON_NN  1016
// 全域變數:
HINSTANCE hInst;                                // 目前執行個體
WCHAR szTitle[MAX_LOADSTRING];                  // 標題列文字
WCHAR szWindowClass[MAX_LOADSTRING];            // 主視窗類別名稱
WCHAR Buffer[100];
int num = 0;
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
    LoadStringW(hInstance, IDC_SIMPLECALCULATORPANEL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 執行應用程式初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPLECALCULATORPANEL));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SIMPLECALCULATORPANEL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SIMPLECALCULATORPANEL);
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
    static HWND hWndEdit = 0;
    static HWND hBtnOne = 0, hBtnTwo = 0, hBtnThree = 0,
                hBtnFour = 0, hBtnFive = 0, hBtnSix = 0, 
                hBtnSeven = 0, hBtnEight = 0, hBtnNine = 0, 
                hBtnZero = 0, hBtnZeroo = 0, hBtnZerooo = 0, 
                hBtnC = 0, hBtnDelete = 0, hBtn = 0, hBtnn = 0;
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
            case IDC_BUTTON_ONE:
            case IDC_BUTTON_TWO:
            case IDC_BUTTON_THREE:
            case IDC_BUTTON_FOUR:
            case IDC_BUTTON_FIVE:
            case IDC_BUTTON_SIX:
            case IDC_BUTTON_SEVEN:
            case IDC_BUTTON_EIGHT:
            case IDC_BUTTON_NINE:
            case IDC_BUTTON_ZERO:
            case IDC_BUTTON_ZEROO:
            case IDC_BUTTON_ZEROOO:
            case IDC_BUTTON_C:
            case IDC_BUTTON_DELETE:
            {
                switch (HIWORD(wParam))
                {
                case BN_CLICKED:
                {                
                    if (num > 31)
                        break;
                    else if(num<31)
                    {
                        if (wmId == IDC_BUTTON_ONE)
                        {                        
                            Buffer[num++] = '1';
                            Buffer[num] = '\0';                                               
                        }
                        if (wmId == IDC_BUTTON_TWO)
                        {
                            Buffer[num++] = '2';
                            Buffer[num] = '\0';                                                    
                        }
                        if (wmId == IDC_BUTTON_THREE)
                        {
                            Buffer[num++] = '3';
                            Buffer[num] = '\0';                                                    
                        }
                        if (wmId == IDC_BUTTON_FOUR)
                        {
                            Buffer[num++] = '4';
                            Buffer[num] = '\0';                                                    
                        }
                        if (wmId == IDC_BUTTON_FIVE)
                        {
                            Buffer[num++] = '5';
                            Buffer[num] = '\0';
                        }
                        if (wmId == IDC_BUTTON_SIX)
                        {
                            Buffer[num++] = '6';
                            Buffer[num] = '\0';
                        }
                        if (wmId == IDC_BUTTON_SEVEN)
                        {
                            Buffer[num++] = '7';
                            Buffer[num] = '\0';
                        }
                        if (wmId == IDC_BUTTON_EIGHT)
                        {
                            Buffer[num++] = '8';
                            Buffer[num] = '\0';
                        }
                        if (wmId == IDC_BUTTON_NINE)
                        {
                            Buffer[num++] = '9';
                            Buffer[num] = '\0';
                        }
                        if (wmId == IDC_BUTTON_ZERO)
                        {
                            if (num != 0)
                            {
                                Buffer[num++] = '0';
                                Buffer[num] = '\0';
                            }
                            else  Buffer[num] = '0';
                        }
                        if (wmId == IDC_BUTTON_ZEROO)
                        {
                            if (num != 0)
                            {
                                if ((num + 2) <= 31)
                                {
                                    Buffer[num++] = '0';
                                    Buffer[num++] = '0';
                                    Buffer[num] = '\0';
                                }
                            }
                            else  Buffer[num] = '0';
                        }
                        if (wmId == IDC_BUTTON_ZEROOO)
                        {
                            if (num != 0)
                            {
                                if ((num + 3) <= 31)
                                {
                                    Buffer[num++] = '0';
                                    Buffer[num++] = '0';
                                    Buffer[num++] = '0';
                                    Buffer[num] = '\0';
                                }
                            }
                            else  Buffer[num] = '0';
                        }
                        
                        SetWindowText(hWndEdit, Buffer);
                    }
                    if (wmId == IDC_BUTTON_C)
                    {
                        num = 0;                        
                        Buffer[0] = '0';
                        Buffer[1] = '\0';
                    }
                    if (wmId == IDC_BUTTON_DELETE)
                    {
                       num--;                       
                       if (num <= 0)
                       {
                           num = 0;
                           Buffer[0] = '0';
                           Buffer[1] = '\0';
                       }
                       else Buffer[num] = '\0';  
                    }
                    SetWindowText(hWndEdit, Buffer);
                }
                break;
                }
                
            }
            break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            
            }
        }
        break;
    case WM_CTLCOLORSTATIC:
        {
            HDC hdcStatic = (HDC)wParam;           // wParam為HDC
            // 設定文字前景與背景色
            SetTextColor(hdcStatic, RGB(0, 0, 0));
            SetBkColor(hdcStatic, RGB(255, 255, 255));
            // 傳回繪製背景的刷子
            return (INT_PTR)CreateSolidBrush(RGB(255, 255, 255));
        }
        break;
    case WM_CREATE:
        {
            // 呼叫CreateWindow()建立控制元件子視窗(佈局)
            // Edit
            hWndEdit = CreateWindow(
                            TEXT("STATIC"),
                            TEXT("0"),
                            WS_VISIBLE | WS_CHILD | WS_BORDER | TA_RIGHT,
                            5, 5, 275, 25,
                            hWnd, 0, hInst, NULL);
            // Button: Change Title
            hBtnOne = CreateWindow(
                            L"BUTTON",  // Predefined class; Unicode assumed 
                            L"1",      // Button text 
                            WS_VISIBLE | WS_CHILD,  // Styles 
                            5, 35, 65, 65,
                            hWnd,
                            (HMENU)IDC_BUTTON_ONE,   // No menu.
                            hInst,
                            NULL);  // Pointer not needed.
            hBtnTwo = CreateWindow(
                            L"BUTTON",  // Predefined class; Unicode assumed 
                            L"2",      // Button text 
                            WS_VISIBLE | WS_CHILD,  // Styles 
                            75, 35, 65, 65,
                            hWnd,
                            (HMENU)IDC_BUTTON_TWO,   // No menu.
                            hInst,
                            NULL);  // Pointer not needed.
            hBtnThree = CreateWindow(
                            L"BUTTON",  // Predefined class; Unicode assumed 
                            L"3",      // Button text 
                            WS_VISIBLE | WS_CHILD,  // Styles 
                            145, 35, 65, 65,
                            hWnd,
                            (HMENU)IDC_BUTTON_THREE,   // No menu.
                            hInst,
                            NULL);  // Pointer not needed.
            hBtnC = CreateWindow(
                            L"BUTTON",  // Predefined class; Unicode assumed 
                            L"C",      // Button text 
                            WS_VISIBLE | WS_CHILD,  // Styles 
                            215, 35, 65, 65,
                            hWnd,
                            (HMENU)IDC_BUTTON_C,   // No menu.
                            hInst,
                            NULL);  // Pointer not needed.
            hBtnFour = CreateWindow(
                            L"BUTTON",  // Predefined class; Unicode assumed 
                            L"4",      // Button text 
                            WS_VISIBLE | WS_CHILD,  // Styles 
                            5, 105, 65, 65,
                            hWnd,
                            (HMENU)IDC_BUTTON_FOUR,   // No menu.
                            hInst,
                            NULL);  // Pointer not needed.
            hBtnFive= CreateWindow(
                            L"BUTTON",  // Predefined class; Unicode assumed 
                            L"5",      // Button text 
                            WS_VISIBLE | WS_CHILD,  // Styles 
                            75, 105, 65, 65,
                            hWnd,
                            (HMENU)IDC_BUTTON_FIVE,   // No menu.
                            hInst,
                            NULL);  // Pointer not needed.
            hBtnSix = CreateWindow(
                L"BUTTON",  // Predefined class; Unicode assumed 
                L"6",      // Button text 
                WS_VISIBLE | WS_CHILD,  // Styles 
                145, 105, 65, 65,
                hWnd,
                (HMENU)IDC_BUTTON_SIX,   // No menu.
                hInst,
                NULL);  // Pointer not needed.
            hBtnDelete = CreateWindow(
                L"BUTTON",  // Predefined class; Unicode assumed 
                L"<-",      // Button text 
                WS_VISIBLE | WS_CHILD,  // Styles 
                215, 105, 65, 65,
                hWnd,
                (HMENU)IDC_BUTTON_DELETE,   // No menu.
                hInst,
                NULL);  // Pointer not needed.
            hBtnSeven = CreateWindow(
                L"BUTTON",  // Predefined class; Unicode assumed 
                L"7",      // Button text 
                WS_VISIBLE | WS_CHILD,  // Styles 
                5, 175, 65, 65,
                hWnd,
                (HMENU)IDC_BUTTON_SEVEN,   // No menu.
                hInst,
                NULL);  // Pointer not needed.
            hBtnEight= CreateWindow(
                L"BUTTON",  // Predefined class; Unicode assumed 
                L"8",      // Button text 
                WS_VISIBLE | WS_CHILD,  // Styles 
                75, 175, 65, 65,
                hWnd,
                (HMENU)IDC_BUTTON_EIGHT,   // No menu.
                hInst,
                NULL);  // Pointer not needed.
            hBtnNine = CreateWindow(
                L"BUTTON",  // Predefined class; Unicode assumed 
                L"9",      // Button text 
                WS_VISIBLE | WS_CHILD,  // Styles 
                145, 175, 65, 65,
                hWnd,
                (HMENU)IDC_BUTTON_NINE,   // No menu.
                hInst,
                NULL);  // Pointer not needed.
            hBtn = CreateWindow(
                L"BUTTON",  // Predefined class; Unicode assumed 
                L"",      // Button text 
                WS_VISIBLE | WS_CHILD,  // Styles 
                215, 175, 65, 65,
                hWnd,
                (HMENU)IDC_BUTTON_N,   // No menu.
                hInst,
                NULL);  // Pointer not needed.
            hBtnZero = CreateWindow(
                L"BUTTON",  // Predefined class; Unicode assumed 
                L"0",      // Button text 
                WS_VISIBLE | WS_CHILD,  // Styles 
                5, 245, 65, 65,
                hWnd,
                (HMENU)IDC_BUTTON_ZERO,   // No menu.
                hInst,
                NULL);  // Pointer not needed.
            hBtnZeroo = CreateWindow(
                L"BUTTON",  // Predefined class; Unicode assumed 
                L"00",      // Button text 
                WS_VISIBLE | WS_CHILD,  // Styles 
                75, 245, 65, 65,
                hWnd,
                (HMENU)IDC_BUTTON_ZEROO,   // No menu.
                hInst,
                NULL);  // Pointer not needed.
            hBtnZerooo = CreateWindow(
                L"BUTTON",  // Predefined class; Unicode assumed 
                L"000",      // Button text 
                WS_VISIBLE | WS_CHILD,  // Styles 
                145, 245, 65, 65,
                hWnd,
                (HMENU)IDC_BUTTON_ZEROOO,   // No menu.
                hInst,
                NULL);  // Pointer not needed.
            hBtnn = CreateWindow(
                L"BUTTON",  // Predefined class; Unicode assumed 
                L"",      // Button text 
                WS_VISIBLE | WS_CHILD,  // Styles 
                215, 245, 65, 65,
                hWnd,
                (HMENU)IDC_BUTTON_NN,   // No menu.
                hInst,
                NULL);  // Pointer not needed.
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此新增任何使用 hdc 的繪圖程式碼...
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
