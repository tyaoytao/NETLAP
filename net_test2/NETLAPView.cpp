
// NETLAPView.cpp : CNETLAPView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNETLAPView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_SAVE, &CNETLAPView::OnFileSave)
END_MESSAGE_MAP()

// CNETLAPView ����/����

CNETLAPView::CNETLAPView()
{
	// TODO: �ڴ˴���ӹ������

}

CNETLAPView::~CNETLAPView()
{
}

BOOL CNETLAPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping
	return bPreCreated;

}

// CNETLAPView ����

void CNETLAPView::OnDraw(CDC* pDC)
{
	CNETLAPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CRect rectClient;
    GetClientRect(&rectClient);
    pDC->SetTextAlign(TA_LEFT|TA_TOP);
	//pDC->DrawText(str,rectClient,DT_WORDBREAK);
	//pDC->TextOut(0,0,str);
	//pDC->SetWindowText(str);
}


// CNETLAPView ��ӡ


void CNETLAPView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CNETLAPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return CEditView::OnPreparePrinting(pInfo);
}

void CNETLAPView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CNETLAPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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
// CNETLAPView ���

#ifdef _DEBUG
void CNETLAPView::AssertValid() const
{
	CEditView::AssertValid();
}

void CNETLAPView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CNETLAPDoc* CNETLAPView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNETLAPDoc)));
	return (CNETLAPDoc*)m_pDocument;
}
#endif //_DEBUG


// CNETLAPView ��Ϣ�������

void CNETLAPView::OnFileSave()
{
	// TODO: Add your command handler code here
	view->GetEditCtrl().GetWindowText(str); 
	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|");   
	// ������ļ��Ի���   
	//CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);   
	CFileDialog fileDlg(FALSE, _T("txt"), NULL, OFN_EXPLORER | OFN_OVERWRITEPROMPT, szFilter, this); 
	CString filePath;  
    // ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg.DoModal())   
	{    
	    filePath = fileDlg.GetPathName();  
		CStdioFile file; 
        if(!file.Open(filePath,CFile::modeCreate|CFile::modeReadWrite,NULL))
		{
			MessageBox("�����ļ�����ʧ�ܣ�","��ʾ",MB_OK);
		}
		else
		{
			file.WriteString(str);
			CNETLAPDoc* pDoc = GetDocument();
			pDoc->SetModifiedFlag(FALSE); 
			file.Close(); 
			MessageBox("�����ļ��ɹ���","��ʾ",MB_OK);
		}
		
	} 
}
