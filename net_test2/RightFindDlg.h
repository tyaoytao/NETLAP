#pragma once


// CRightFindDlg dialog

class CRightFindDlg : public CDialog
{
	DECLARE_DYNAMIC(CRightFindDlg)

public:
	CRightFindDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRightFindDlg();

// Dialog Data
	enum { IDD = IDD_RightFind_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRightfindButton();
	afx_msg void OnBnClickedBreakButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPatternButton();
};
