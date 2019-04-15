#pragma once
#include"fstream";
#include"public.h"
#include"PWDResetDlg.h"
// LoginDlg 对话框

class LoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LoginDlg)

public:
	LoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LoginDlg();

// 密码文件
	CString m_csLoginFolderPath = rootFolder + _T("pwd");
	CString m_csLoginFilePath;
// 对话框数据
	enum { IDD = IDD_LOGIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_csUser;
	CString m_csPassWD;
	afx_msg void OnBnClickedLoginButton();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedResetButton();
};
