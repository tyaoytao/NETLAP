#pragma once


// CRightFingDlg dialog

class CRightFingDlg : public CDialog
{
	DECLARE_DYNAMIC(CRightFingDlg)

public:
	CRightFingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRightFingDlg();

// Dialog Data
	enum { IDD = IDD_RightFind_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
