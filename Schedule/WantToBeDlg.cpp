// WantToBeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Schedule.h"
#include "WantToBeDlg.h"
#include "afxdialogex.h"


// WantToBeDlg �Ի���

IMPLEMENT_DYNAMIC(WantToBeDlg, CDialogEx)

WantToBeDlg::WantToBeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(WantToBeDlg::IDD, pParent)
	, m_csSaveStatus(_T(""))
	, m_csWTBContent(_T(""))
	, m_csNowContent(_T(""))
{

}

WantToBeDlg::~WantToBeDlg()
{
}

void WantToBeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SAVE_STATUS_EDIT, m_csSaveStatus);
	DDX_Text(pDX, IDC_WANT_TO_BE_EDIT, m_csWTBContent);
	DDX_Text(pDX, IDC_NOW_ME_EDIT, m_csNowContent);
}


BEGIN_MESSAGE_MAP(WantToBeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &WantToBeDlg::OnBnClickedSaveButton)
END_MESSAGE_MAP()


// WantToBeDlg ��Ϣ�������


BOOL WantToBeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��������
	CEdit* m_edWTBContent = (CEdit *)GetDlgItem(IDC_WANT_TO_BE_EDIT);
	CEdit* m_edNowContent = (CEdit *)GetDlgItem(IDC_NOW_ME_EDIT);
	font.CreatePointFont(130, _T("����"));     //ѡ������
	m_edWTBContent->SetFont(&font);
	m_edNowContent->SetFont(&font);

	m_csWTBFilePath = m_csWTBFolderPath + _T("\\wtb.sch");
	if (PathFileExists(m_csWTBFilePath)){
		readWTBFile(m_csWTBFilePath);
	}
	else{
		m_csWTBContent = _T("���ͣ���-��");
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
void WantToBeDlg::readWTBFile(CString filePath){
	CFile file;
	if (file.Open(filePath, CFile::modeRead) == 0)
	{
		MessageBox("��ȡ�ļ�ʧ��!", NULL, MB_ICONEXCLAMATION);
		return;
	}
	int size = file.GetLength();
	char* pText = new char[size + 1];
	int nRet = file.Read(pText, size);
	file.Close();
	pText[nRet] = 0;
	//��ȡ�����Ϊ���ˡ�
	CString csMsg(pText);
	int n = csMsg.Find("==");
	m_csWTBContent = csMsg.Left(n);
	//��ȡ�����ڡ�
	int length = csMsg.Delete(0, n + 2);
	m_csNowContent = csMsg.Right(length);
	UpdateData(FALSE);
}
void WantToBeDlg::OnBnClickedSaveButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CreatMultiDir(m_csWTBFolderPath);
	CFile file;
	if (file.Open(m_csWTBFilePath, CFile::modeWrite | CFile::modeCreate) == 0)
	{
		MessageBox(m_csWTBFilePath + _T("����ʧ��!"), NULL, MB_ICONEXCLAMATION);
		return;
	}
	//���桰���Ϊ���ˡ�
	CString strSplit = "==";
	file.Write(m_csWTBContent, m_csWTBContent.GetLength());
	file.Write(strSplit, strSplit.GetLength());//�ָ��
	//���桰���ڡ�
	file.Write(m_csNowContent, m_csNowContent.GetLength());
	file.Flush();
	file.Close();

	m_csSaveStatus = "=>";
	UpdateData(FALSE);
}
