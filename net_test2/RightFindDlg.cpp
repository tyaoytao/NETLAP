// RightFindDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NETLAP.h"
#include "NETLAPView.h"
#include "RightFindDlg.h"
#include "Right_net.h"
#include "PatternDlg.h"
extern CString pattern;
extern CString str;
extern CNETLAPView* view;
CRightFindDlg* rDlg;
// CRightFindDlg dialog

IMPLEMENT_DYNAMIC(CRightFindDlg, CDialog)

CRightFindDlg::CRightFindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRightFindDlg::IDD, pParent)
{

}

CRightFindDlg::~CRightFindDlg()
{
}

void CRightFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRightFindDlg, CDialog)
	ON_BN_CLICKED(IDC_RightFind_Button, &CRightFindDlg::OnBnClickedRightfindButton)
	ON_BN_CLICKED(IDC_Break_Button, &CRightFindDlg::OnBnClickedBreakButton)
	ON_BN_CLICKED(IDC_Pattern_Button, &CRightFindDlg::OnBnClickedPatternButton)
END_MESSAGE_MAP()


// CRightFindDlg message handlers

void CRightFindDlg::OnBnClickedRightfindButton()
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
		MessageBox(_T("请打开一个序列文件！"),_T("提示"));
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
	    CRight_net right_net;
		right_net.convert_p_to_ruler(p);
		DWORD begintime=GetTickCount();
		right_net.nonoverlength(minlen,maxlen);
		DWORD endtime=GetTickCount();
		CString time,num,occ;
		time.Format("%d",(endtime-begintime));
		num.Format("%d",right_net.store.size());
		SetDlgItemText (IDC_Time_Edit,time);
		SetDlgItemText (IDC_Number_Edit,num);
		SetDlgItemText (IDC_Occurrence_Edit,right_net.displayocc());
	}
}

void CRightFindDlg::OnBnClickedBreakButton()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}



BOOL CRightFindDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	rDlg = this;
	// TODO:  Add extra initialization here
	SetDlgItemText (IDC_Pattern_Edit,pattern);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CRightFindDlg::OnBnClickedPatternButton()
{
	// TODO: Add your control notification handler code here
	CPatternDlg* dlg = new CPatternDlg;
	dlg->Create(MAKEINTRESOURCE(IDD_Pattern_Dialog));
	dlg->ShowWindow(1);
	dlg->CenterWindow();
}
