
// NETLAPDoc.cpp : CNETLAPDoc ���ʵ��
//

#include "stdafx.h"
#include "NETLAP.h"

#include "NETLAPDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNETLAPDoc

IMPLEMENT_DYNCREATE(CNETLAPDoc, CDocument)

BEGIN_MESSAGE_MAP(CNETLAPDoc, CDocument)
END_MESSAGE_MAP()


// CNETLAPDoc ����/����

CNETLAPDoc::CNETLAPDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CNETLAPDoc::~CNETLAPDoc()
{
}

BOOL CNETLAPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CNETLAPDoc ���л�

void CNETLAPDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CNETLAPDoc ���

#ifdef _DEBUG
void CNETLAPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNETLAPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CNETLAPDoc ����

BOOL CNETLAPDoc::CanCloseFrame(CFrameWnd* pFrame)
{
	// TODO: Add your specialized code here and/or call the base class
	SetModifiedFlag(FALSE); 
	return CDocument::CanCloseFrame(pFrame);
}
