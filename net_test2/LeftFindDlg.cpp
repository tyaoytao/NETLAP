// LeftFindDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NETLAP.h"
#include "NETLAPView.h"
#include "LeftFindDlg.h"
#include "Left_net.h"
#include "PatternDlg.h"
extern CString str;
extern CString pattern;
extern CNETLAPView* view;
CLeftFindDlg* lDlg;
// CLeftFindDlg dialog

IMPLEMENT_DYNAMIC(CLeftFindDlg, CDialog)

CLeftFindDlg::CLeftFindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLeftFindDlg::IDD, pParent)
{
	

}

CLeftFindDlg::~CLeftFindDlg()
{
}

void CLeftFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLeftFindDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CLeftFindDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_LeftFind_Button, &CLeftFindDlg::OnBnClickedLeftfindButton)
	ON_BN_CLICKED(IDC_Pattern_Button, &CLeftFindDlg::OnBnClickedPatternButton)
END_MESSAGE_MAP()


// CLeftFindDlg message handlers

void CLeftFindDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CLeftFindDlg::OnBnClickedLeftfindButton()
{
	// TODO: Add your control notification handler code here
	view->GetEditCtrl().GetWindowText(str); 
	CString tb_minlen,tb_maxlen,tb_pattern;
	int minlen,maxlen;
	char p[1000];
	GetDlgItemText (IDC_Minlen_Edit,tb_minlen);
	GetDlgItemText (IDC_Maxlen_Edit,tb_maxlen);
	GetDlgItemText (IDC_Pattern_Edit,tb_pattern);
	if(str.IsEmpty())
	{
		MessageBox(_T("请打开或输入一个序列文件！"),_T("提示"));
	}
	else if(tb_minlen.IsEmpty())
	{
		MessageBox(_T("请输入最小长度！"),_T("提示"));
	}
	else if(tb_maxlen.IsEmpty())
	{
		MessageBox(_T("请输入最大长度！"),_T("提示"));
	}
	else if(tb_pattern.IsEmpty())
	{
		MessageBox(_T("请输入模式串！"),_T("提示"));
	}
	else
	{
		minlen = atoi(tb_minlen);
		maxlen = atoi(tb_maxlen);
		int length = tb_pattern.GetLength() + 1;
		//memset(p,0, sizeof(bool) * 100);
		//strncpy(p,(LPCTSTR)tb_pattern,sizeof(p)); 
		strcpy(p,tb_pattern);
	    CLeft_net left_net;
		left_net.convert_p_to_ruler(p);
		DWORD begintime=GetTickCount();
		left_net.nonoverlength(minlen,maxlen);
		DWORD endtime=GetTickCount();
		CString time,num,occ;
		time.Format("%d",(endtime-begintime));
		num.Format("%d",left_net.store.size());
		SetDlgItemText (IDC_Time_Edit,time);
		SetDlgItemText (IDC_Number_Edit,num);
		SetDlgItemText (IDC_Occurrence_Edit,left_net.displayocc());
	}
}

//BOOL CLeftFindDlg::OnInitDialog()
//{
//	CDialog::OnInitDialog();
//	hAccel = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(ID_32771));
//	// TODO:  Add extra initialization here
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// EXCEPTION: OCX Property Pages should return FALSE
//}


BOOL CLeftFindDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	if   (hAccel)   
	{ 
		if   (::TranslateAccelerator(m_hWnd,  hAccel,   pMsg))   
		{ 
			return(TRUE); 
		} 
	} 
	return   CDialog::PreTranslateMessage(pMsg); 
}

BOOL CLeftFindDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	lDlg = this;
	// TODO:  Add extra initialization here
	SetDlgItemText (IDC_Pattern_Edit,pattern);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CLeftFindDlg::OnBnClickedPatternButton()
{
	// TODO: Add your control notification handler code here
	CPatternDlg* dlg = new CPatternDlg;
	dlg->Create(MAKEINTRESOURCE(IDD_Pattern_Dialog));
	dlg->ShowWindow(1);
	dlg->CenterWindow();
}
