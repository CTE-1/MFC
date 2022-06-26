﻿
// ChildView.h: CChildView 類別的介面
//


#pragma once

#include "CSwapNumberWnd.h"
// CChildView 視窗

class CChildView : public CWnd
{
// 建構
public:
	CChildView();

// 屬性
public:

// 作業
public:

// 覆寫
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 程式碼實作
public:
	virtual ~CChildView();

	// 產生的訊息對應函式
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	CSwapNumberWnd m_wndNums[10];
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void Relayout();
	LRESULT OnSwapRequest(WPARAM wParam, LPARAM lParam);
};

