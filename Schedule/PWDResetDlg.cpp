// PWDResetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Schedule.h"
#include "PWDResetDlg.h"
#include "afxdialogex.h"


// PWDResetDlg 对话框

IMPLEMENT_DYNAMIC(PWDResetDlg, CDialogEx)

PWDResetDlg::PWDResetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(PWDResetDlg::IDD, pParent)
	, m_csOldUser(_T(""))
	, m_csOldPWD(_T(""))
	, m_csNewUser(_T(""))
	, m_csNewPWD1(_T(""))
	, m_csNewPWD2(_T(""))
{

}

PWDResetDlg::~PWDResetDlg()
{
}

void PWDResetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OLD_USER_CONTENT_EDIT, m_csOldUser);
	DDX_Text(pDX, IDC_OLD_PWD_CONTENT_EDIT, m_csOldPWD);
	DDX_Text(pDX, IDC_NEW_USER_CONTENT_EDIT, m_csNewUser);
	DDX_Text(pDX, IDC_NEW_PWD_CONTENT_EDIT, m_csNewPWD1);
	DDX_Text(pDX, IDC_NEW_PWD_CONTENT_EDIT2, m_csNewPWD2);
}


BEGIN_MESSAGE_MAP(PWDResetDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RESET_BUTTON, &PWDResetDlg::OnBnClickedResetButton)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, &PWDResetDlg::OnBnClickedClearButton)
END_MESSAGE_MAP()


// PWDResetDlg 消息处理程序


BOOL PWDResetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//密码文件
	m_csLoginFilePath = m_csLoginFolderPath + _T("\\.pd");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void PWDResetDlg::OnBnClickedResetButton()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	CreatMultiDir(m_csLoginFolderPath);
	if (m_csNewPWD1 != m_csNewPWD2){
		AfxMessageBox(_T("新输入的密码不一致！"));
		return;
	}
	//读入原始密码
	CString user, passwd;
	if (!PathFileExists(m_csLoginFilePath)){
		user = "root";
		passwd = "admin";
	}
	else{
		string temp;
		ifstream  file;
		file.open(m_csLoginFilePath, ofstream::binary);
		getline(file, temp, '\n');
		user = decode(temp).c_str();
		getline(file, temp, '\n');
		passwd = decode(temp).c_str();
		file.close();
	}
	if (m_csOldUser != user || m_csOldPWD != passwd){
		AfxMessageBox(_T("旧用户名或者密码错误！"));
		return;
	}
	//USES_CONVERSION;
	string temp_str = m_csNewUser.GetBuffer();
	string temp = encode(temp_str);
	ofstream file;
	file.open(m_csLoginFilePath, ofstream::binary);
	file << temp << "\n";
	temp_str = m_csNewPWD1.GetBuffer(0);
	temp = encode(temp_str);
	file << temp << '\n';
	file.close();
	AfxMessageBox(_T("更改成功！"));
}


void PWDResetDlg::OnBnClickedClearButton()
{
	// TODO:  在此添加控件通知处理程序代码
	m_csOldUser = "";
	m_csOldPWD = "";
	m_csNewUser = "";
	m_csNewPWD1 = "";
	m_csNewPWD2 = "";
	UpdateData(FALSE);
}
