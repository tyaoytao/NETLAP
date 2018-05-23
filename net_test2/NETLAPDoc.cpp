
// NETLAPDoc.cpp : CNETLAPDoc 类的实现
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


// CNETLAPDoc 构造/析构

CNETLAPDoc::CNETLAPDoc()
{
	// TODO: 在此添加一次性构造代码

}

CNETLAPDoc::~CNETLAPDoc()
{
}

BOOL CNETLAPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CNETLAPDoc 序列化

void CNETLAPDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CNETLAPDoc 诊断

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


// CNETLAPDoc 命令

BOOL CNETLAPDoc::CanCloseFrame(CFrameWnd* pFrame)
{
	// TODO: Add your specialized code here and/or call the base class
	SetModifiedFlag(FALSE); 
	return CDocument::CanCloseFrame(pFrame);
}
