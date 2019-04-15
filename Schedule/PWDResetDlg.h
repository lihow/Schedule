#pragma once
#include"fstream";
#include"public.h"

// PWDResetDlg 对话框

class PWDResetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PWDResetDlg)

public:
	PWDResetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PWDResetDlg();
// 密码文件
	CString m_csLoginFolderPath = rootFolder + _T("pwd");
	CString m_csLoginFilePath;
// 对话框数据
	enum { IDD = IDD_PWD_RESET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
