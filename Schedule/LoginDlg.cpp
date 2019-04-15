// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Schedule.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// LoginDlg �Ի���

IMPLEMENT_DYNAMIC(LoginDlg, CDialogEx)

LoginDlg::LoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(LoginDlg::IDD, pParent)
	, m_csUser(_T(""))
	, m_csPassWD(_T(""))
{

}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USER_CONTENT_EDIT, m_csUser);
	DDX_Text(pDX, IDC_PASSWD_CONTENT_EDIT, m_csPassWD);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_LOGIN_BUTTON, &LoginDlg::OnBnClickedLoginButton)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RESET_BUTTON, &LoginDlg::OnBnClickedResetButton)
END_MESSAGE_MAP()


// LoginDlg ��Ϣ�������
void LoginDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(217, 226, 241));
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}

BOOL LoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CEdit *m_title = (CEdit *)GetDlgItem(IDC_LOGIN__TITLE_STATIC);
	CFont  font;
	font.CreatePointFont(630, _T("����"));     //ѡ������
	m_title->SetFont(&font);
	//�����ļ�
	m_csLoginFilePath = m_csLoginFolderPath + _T("\\.pd");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void LoginDlg::OnBnClickedLoginButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	UpdateData(true);
	if (m_csUser == user && m_csPassWD == passwd){
		CDialog::OnOK();
	}
	else{
		AfxMessageBox(_T("�û��������������"));
	}
}

void LoginDlg::OnBnClickedResetButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	PWDResetDlg resetDlg;
	resetDlg.DoModal();
}
