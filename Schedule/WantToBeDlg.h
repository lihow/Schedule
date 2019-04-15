#pragma once
#include "afxwin.h"
#include "public.h"

// WantToBeDlg �Ի���

class WantToBeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WantToBeDlg)

public:
	WantToBeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WantToBeDlg();

//����·��
	CString m_csWTBFolderPath = rootFolder + "wtb";
	CString m_csWTBFilePath;
	void readWTBFile(CString filePath);

// �Ի�������
	enum { IDD = IDD_WANT_TO_BE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSaveButton();
	CString m_csSaveStatus;
	CString m_csWTBContent;
	CString m_csNowContent;
	CFont font;
};
