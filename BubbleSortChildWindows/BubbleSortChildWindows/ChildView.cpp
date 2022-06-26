
// ChildView.cpp: CChildView 類別的實作
//

#include "pch.h"
#include "framework.h"
#include "BubbleSortChildWindows.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CSwapNumberWnd.h"


// CChildView

CChildView::CChildView()
{
	CSwapNumberWnd::m_nRandDenum = 100;
	CSwapNumberWnd::m_font.CreateFont(48, 0, 0, 0, FW_BOLD, 0,
		0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, _T("Microsoft Sans Serif"));
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_SWAP_REQUEST, &CChildView::OnSwapRequest)
END_MESSAGE_MAP()



// CChildView 訊息處理常式

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 繪製的裝置內容
	
	// TODO: 在此加入您的訊息處理常式程式碼
	
	// 不要呼叫描繪訊息的 CWnd::OnPaint()
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此加入特別建立的程式碼

	CRect rect(0, 0, 80, 80);
	for (int i = 0; i < 10; i++) {
		m_wndNums[i].Create(NULL, _T(""),
			WS_CHILD | WS_VISIBLE, rect, this, 100 + i);
		rect.OffsetRect(80, 0);
	}

	return 0;
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此加入您的訊息處理常式程式碼
	Relayout();
}

void CChildView::Relayout()
{
	CRect rect;
	GetClientRect(&rect);
	int x = (rect.Width() - 80 * 10) / 2;
	int y = (rect.Height() - 80) / 2;

	rect = CRect(x, y, x + 80, y + 80);
	for (int i = 0; i < 10; i++) {
		m_wndNums[i].MoveWindow(&rect);
		rect.OffsetRect(80, 0);
	}
}

LRESULT CChildView::OnSwapRequest(WPARAM wParam, LPARAM lParam)
{
	UINT id = wParam;
	TRACE(_T("%d\n"), id);

	if (id >= 109) return 0;
	id -= 100;
	
	int a, b;
	a = m_wndNums[id].m_nCurrentValue;
	b = m_wndNums[id + 1].m_nCurrentValue;

	m_wndNums[id].m_nCurrentValue = b;
	m_wndNums[id + 1].m_nCurrentValue = a;

	m_wndNums[id].Invalidate();
	m_wndNums[id + 1].Invalidate();

	return 0;
}

