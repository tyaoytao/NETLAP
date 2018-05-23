
// NETLAPView.h : CNETLAPView ��Ľӿ�
//


#pragma once

#include "NETLAPDoc.h"
class CNETLAPView : public CEditView
{
protected: // �������л�����
	CNETLAPView();
	DECLARE_DYNCREATE(CNETLAPView)

// ����
public:
	CNETLAPDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CNETLAPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileSave();
};

#ifndef _DEBUG  // NETLAPView.cpp �еĵ��԰汾
inline CNETLAPDoc* CNETLAPView::GetDocument() const
   { return reinterpret_cast<CNETLAPDoc*>(m_pDocument); }
#endif
