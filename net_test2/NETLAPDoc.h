
// NETLAPDoc.h : CNETLAPDoc ��Ľӿ�
//


#pragma once


class CNETLAPDoc : public CDocument
{
protected: // �������л�����
	CNETLAPDoc();
	DECLARE_DYNCREATE(CNETLAPDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CNETLAPDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileSave();
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
};


