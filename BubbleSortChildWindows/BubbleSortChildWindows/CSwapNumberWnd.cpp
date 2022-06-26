// CSwapNumberWnd.cpp: 實作檔案
//

#include "pch.h"
#include "BubbleSortChildWindows.h"
#include "CSwapNumberWnd.h"


// CSwapNumberWnd

IMPLEMENT_DYNAMIC(CSwapNumberWnd, CWnd)

int CSwapNumberWnd::m_nRandDenum = 100;
CFont CSwapNumberWnd::m_font;

CSwapNumberWnd::CSwapNumberWnd()
{

}

CSwapNumberWnd::~CSwapNumberWnd()
{
}


BEGIN_MESSAGE_MAP(CSwapNumberWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CSwapNumberWnd 訊息處理常式




int CSwapNumberWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此加入特別建立的程式碼

	m_nCurrentValue = rand() % m_nRandDenum;
	return 0;
}

void CSwapNumberWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_bDown = TRUE;
	Invalidate();
	GetParent()->SendMessage(WM_SWAP_REQUEST, GetDlgCtrlID());
	CWnd::OnLButtonDown(nFlags, point);
}


void CSwapNumberWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_bDown = FALSE;
	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CSwapNumberWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	CRect rect;
	GetClientRect(&rect);
	CGdiObject* pOldPen = pDC->SelectStockObject(BLACK_PEN);
	CGdiObject* pOldBrush = pDC->SelectStockObject(LTGRAY_BRUSH);
	pDC->Rectangle(&rect);

	int n = 5;
	while (n--) {
		rect.DeflateRect(1, 1);
		if (m_bDown)
		{
			pDC->Draw3dRect(&rect, RGB(32, 32, 32), RGB(220, 220, 220));
		}
		else
		{
			pDC->Draw3dRect(&rect, RGB(220, 220, 220), RGB(32, 32, 32));
		}
	}
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

	return TRUE;
}

void CSwapNumberWnd::OnPaint()
{
	CPaintDC dc(this); 	// device context for painting
		// TODO: 在此加入您的訊息處理常式程式碼
		// 不要呼叫圖片訊息的 CWnd::OnPaint()
	CString text;
	text.Format(_T("%d"), m_nCurrentValue);

	CRect rect;
	GetClientRect(&rect);

	CGdiObject* pOldFont = dc.SelectObject(&m_font);
	dc.SetTextColor(RGB(0, 0, 0));
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(text, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	dc.SelectObject(&m_font);
}

