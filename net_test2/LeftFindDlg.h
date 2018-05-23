#pragma once


// CLeftFindDlg dialog

class CLeftFindDlg : public CDialog
{
	DECLARE_DYNAMIC(CLeftFindDlg)

public:
	CLeftFindDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLeftFindDlg();

// Dialog Data
	enum { IDD = IDD_LeftFind_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedLeftfindButton();
//	virtual BOOL OnInitDialog();
	HACCEL hAccel;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPatternButton();
};
