// PatternDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NETLAP.h"
#include "PatternDlg.h"
#include "LeftFindDlg.h"
#include "RightFindDlg.h"
extern CLeftFindDlg* lDlg;
extern CRightFindDlg* rDlg;
CString pattern;

// CPatternDlg dialog

IMPLEMENT_DYNAMIC(CPatternDlg, CDialog)

CPatternDlg::CPatternDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPatternDlg::IDD, pParent)
{

}

CPatternDlg::~CPatternDlg()
{
}

void CPatternDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatternDlg, CDialog)
	ON_BN_CLICKED(IDC_PatternFile_Button, &CPatternDlg::OnBnClickedPatternfileButton)
	ON_BN_CLICKED(IDC_Pattern_Button, &CPatternDlg::OnBnClickedPatternButton)
	ON_BN_CLICKED(IDC_Cancel_Button, &CPatternDlg::OnBnClickedCancelButton)
END_MESSAGE_MAP()


// CPatternDlg message handlers

void CPatternDlg::OnBnClickedPatternfileButton()
{
	// TODO: Add your control notification handler code here
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|");   
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);   
	CString filePath,tmp,pattern;  
	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())   
	{    
		filePath = fileDlg.GetPathName();  
		CStdioFile file; 
		file.Open(filePath,CFile::modeRead,0);    
		while(file.ReadString(tmp))
		{
			pattern.Append(tmp);
		}
		file.Close(); 
		SetDlgItemText (IDC_Pattern_Edit,pattern);

	}   
}

void CPatternDlg::OnBnClickedPatternButton()
{
	// TODO: Add your control notification handler code here
	GetDlgItemText (IDC_Pattern_Edit,pattern);
	if(lDlg != NULL)
	{
		lDlg->OnInitDialog();
	}
	if(rDlg != NULL)
	{
		rDlg->OnInitDialog();
	}
	this->ShowWindow(SW_HIDE);

}

BOOL CPatternDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if   (m_hAccel)   
      { 
            if   (::TranslateAccelerator(m_hWnd,   m_hAccel,   pMsg))   
            { 
                  return(TRUE); 
            } 
      } 
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CPatternDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	if(!pattern.IsEmpty())
		SetDlgItemText (IDC_Pattern_Edit,pattern);
	// TODO:  Add extra initialization here
	//m_hAccel   =   ::LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDD_Pattern_Dialog)); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPatternDlg::OnBnClickedCancelButton()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
