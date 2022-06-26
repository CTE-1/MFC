#pragma once


// CSwapNumberWnd

class CSwapNumberWnd : public CWnd
{
	DECLARE_DYNAMIC(CSwapNumberWnd)

public:
	CSwapNumberWnd();
	virtual ~CSwapNumberWnd();

// 成員變數
public:
	static int m_nRandDenum;
	static CFont m_font;
	int m_nCurrentValue;
	BOOL m_bDown;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	BOOL OnEraseBkgnd(CDC* pDC);
	void OnPaint();
};


