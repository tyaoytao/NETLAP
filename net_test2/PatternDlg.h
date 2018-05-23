#pragma once


// CPatternDlg dialog

class CPatternDlg : public CDialog
{
	DECLARE_DYNAMIC(CPatternDlg)

public:
	CPatternDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPatternDlg();

// Dialog Data
	enum { IDD = IDD_Pattern_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPatternfileButton();
	afx_msg void OnBnClickedPatternButton();
	HACCEL   m_hAccel; 
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancelButton();
};
