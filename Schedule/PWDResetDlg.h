#pragma once
#include"fstream";
#include"public.h"

// PWDResetDlg �Ի���

class PWDResetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PWDResetDlg)

public:
	PWDResetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PWDResetDlg();
// �����ļ�
	CString m_csLoginFolderPath = rootFolder + _T("pwd");
	CString m_csLoginFilePath;
// �Ի�������
	enum { IDD = IDD_PWD_RESET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedResetButton();
	CString m_csOldUser;
	CString m_csOldPWD;
	CString m_csNewUser;
	CString m_csNewPWD1;
	CString m_csNewPWD2;
	afx_msg void OnBnClickedClearButton();
};
