
// NETLAPView.cpp : CNETLAPView 类的实现
//

#include "stdafx.h"
#include "NETLAP.h"

#include "NETLAPDoc.h"
#include "NETLAPView.h"
extern CString str;
CNETLAPView* view = NULL;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNETLAPView

IMPLEMENT_DYNCREATE(CNETLAPView, CEditView)

BEGIN_MESSAGE_MAP(CNETLAPView, CEditView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNETLAPView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_SAVE, &CNETLAPView::OnFileSave)
END_MESSAGE_MAP()

// CNETLAPView 构造/析构

CNETLAPView::CNETLAPView()
{
	// TODO: 在此处添加构造代码

}

CNETLAPView::~CNETLAPView()
{
}

BOOL CNETLAPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping
	return bPreCreated;

}

// CNETLAPView 绘制

void CNETLAPView::OnDraw(CDC* pDC)
{
	CNETLAPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	CRect rectClient;
    GetClientRect(&rectClient);
    pDC->SetTextAlign(TA_LEFT|TA_TOP);
	//pDC->DrawText(str,rectClient,DT_WORDBREAK);
	//pDC->TextOut(0,0,str);
	//pDC->SetWindowText(str);
}


// CNETLAPView 打印


void CNETLAPView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CNETLAPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return CEditView::OnPreparePrinting(pInfo);
}

void CNETLAPView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 添加额外的打印前进行的初始化过程
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CNETLAPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CNETLAPView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CNETLAPView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}
void CNETLAPView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	SetWindowText(str);
}
void CNETLAPView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	//CEditView::GetEditCtrl().SetReadOnly();
	if(!view)
        view = this;
}
// CNETLAPView 诊断

#ifdef _DEBUG
void CNETLAPView::AssertValid() const
{
	CEditView::AssertValid();
}

void CNETLAPView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CNETLAPDoc* CNETLAPView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNETLAPDoc)));
	return (CNETLAPDoc*)m_pDocument;
}
#endif //_DEBUG


// CNETLAPView 消息处理程序

void CNETLAPView::OnFileSave()
{
	// TODO: Add your command handler code here
	view->GetEditCtrl().GetWindowText(str); 
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|");   
	// 构造打开文件对话框   
	//CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);   
	CFileDialog fileDlg(FALSE, _T("txt"), NULL, OFN_EXPLORER | OFN_OVERWRITEPROMPT, szFilter, this); 
	CString filePath;  
    // 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())   
	{    
	    filePath = fileDlg.GetPathName();  
		CStdioFile file; 
        if(!file.Open(filePath,CFile::modeCreate|CFile::modeReadWrite,NULL))
		{
			MessageBox("保存文件操作失败！","提示",MB_OK);
		}
		else
		{
			file.WriteString(str);
			CNETLAPDoc* pDoc = GetDocument();
			pDoc->SetModifiedFlag(FALSE); 
			file.Close(); 
			MessageBox("保存文件成功！","提示",MB_OK);
		}
		
	} 
}
