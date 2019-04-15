// ShortPlanDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Schedule.h"
#include "ShortPlanDlg.h"
#include "afxdialogex.h"


// ShortPlanDlg �Ի���

IMPLEMENT_DYNAMIC(ShortPlanDlg, CDialogEx)

ShortPlanDlg::ShortPlanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ShortPlanDlg::IDD, pParent)
	, m_csDayOfWeek(_T(""))
	, m_csDayOfMonth(_T(""))
	, m_csWeeklyPlanContent(_T(""))
	, m_csMonthlyPlanContent(_T(""))
{

}

ShortPlanDlg::~ShortPlanDlg()
{
}

void ShortPlanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CUR_WEEK_EDIT, m_csDayOfWeek);
	DDX_Text(pDX, IDC_CUR_DATE_EDIT, m_csDayOfMonth);
	DDX_Text(pDX, IDC_WEEKLY_EDIT, m_csWeeklyPlanContent);
	DDX_Text(pDX, IDC_MOUTHLY_EDIT, m_csMonthlyPlanContent);
}


BEGIN_MESSAGE_MAP(ShortPlanDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &ShortPlanDlg::OnBnClickedSaveButton)
END_MESSAGE_MAP()


// ShortPlanDlg ��Ϣ�������
const CString week[] = { "��", "һ", "��", "��", "��", "��", "��" };

BOOL ShortPlanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��õ�ǰ����
	time_t cur_time = time(0);
	tm *ltm = localtime(&cur_time);
	int iDayOfWeek = ltm->tm_wday;
	int iDayOfMonth = ltm->tm_mday;
	m_csDayOfWeek = _T("����") + week[iDayOfWeek];
	m_csDayOfMonth.Format("%d ��", iDayOfMonth);
	//��ȡ�ļ�����
	m_csSPFilePath = m_csSPFolderPath + _T("\\sp.sch");
	if (PathFileExists(m_csSPFilePath)){
		ReadLPFile(m_csSPFilePath);
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void ShortPlanDlg::ReadLPFile(CString filePath){
	CFile file;
	if (file.Open(filePath, CFile::modeRead) == 0)
	{
		MessageBox(filePath + "��ȡ�ļ�ʧ��!", NULL, MB_ICONEXCLAMATION);
		return;
	}
	int size = file.GetLength();
	char* pText = new char[size + 1];
	int nRet = file.Read(pText, size);
	file.Close();
	pText[nRet] = 0;
	//�����ܼƻ�
	CString csMsg(pText);
	int n = csMsg.Find("==");
	m_csWeeklyPlanContent = csMsg.Left(n);
	//�����¼ƻ�
	int length = csMsg.Delete(0, n + 2);
	m_csMonthlyPlanContent = csMsg.Right(length);
	UpdateData(false);
}
void ShortPlanDlg::OnBnClickedSaveButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CreatMultiDir(m_csSPFolderPath);
	CFile file;
	if (file.Open(m_csSPFilePath, CFile::modeWrite | CFile::modeCreate) == 0)
	{
		MessageBox(m_csSPFilePath + _T("����ʧ��!"), NULL, MB_ICONEXCLAMATION);
		return;
	}
	CString strSplit = "==";
	//д���ܼƻ�
	file.Write(m_csWeeklyPlanContent, m_csWeeklyPlanContent.GetLength());
	file.Write(strSplit, strSplit.GetLength());
	//д���¼ƻ�
	file.Write(m_csMonthlyPlanContent, m_csMonthlyPlanContent.GetLength());
	file.Flush();
	file.Close();
}
