#pragma once
#include"fstream";
#include"public.h"
#include"PWDResetDlg.h"
// LoginDlg �Ի���

class LoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LoginDlg)

public:
	LoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LoginDlg();

// �����ļ�
	CString m_csLoginFolderPath = rootFolder + _T("pwd");
	CString m_csLoginFilePath;
// �Ի�������
	enum { IDD = IDD_LOGIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_csUser;
	CString m_csPassWD;
	afx_msg void OnBnClickedLoginButton();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedResetButton();
};
