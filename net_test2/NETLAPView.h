
// NETLAPView.h : CNETLAPView 类的接口
//


#pragma once

#include "NETLAPDoc.h"
class CNETLAPView : public CEditView
{
protected: // 仅从序列化创建
	CNETLAPView();
	DECLARE_DYNCREATE(CNETLAPView)

// 属性
public:
	CNETLAPDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CNETLAPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileSave();
};

#ifndef _DEBUG  // NETLAPView.cpp 中的调试版本
inline CNETLAPDoc* CNETLAPView::GetDocument() const
   { return reinterpret_cast<CNETLAPDoc*>(m_pDocument); }
#endif

