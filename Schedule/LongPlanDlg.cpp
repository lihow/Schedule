// LongPlanDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Schedule.h"
#include "LongPlanDlg.h"
#include "afxdialogex.h"


// LongPlanDlg �Ի���

IMPLEMENT_DYNAMIC(LongPlanDlg, CDialogEx)

LongPlanDlg::LongPlanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(LongPlanDlg::IDD, pParent)
	, m_csSinceYear(_T(""))
	, m_csSinceMouth(_T(""))
	, m_cs3MouthContent(_T(""))
	, m_cs5YearContent(_T(""))
	, m_cs1YearContent(_T(""))
	, m_cs3MouthDeadline(_T(""))
	, m_cs1YearDeadline(_T(""))
	, m_cs5YearDeadline(_T(""))
{

}

LongPlanDlg::~LongPlanDlg()
{
}

void LongPlanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SINE_YEAR_EDIT, m_csSinceYear);
	DDX_Text(pDX, IDC_SINCE_MOUTH_EDIT, m_csSinceMouth);
	DDX_Text(pDX, IDC_3MOUTH_EDIT, m_cs3MouthContent);
	DDX_Text(pDX, IDC_5YEAR_EDIT, m_cs5YearContent);
	DDX_Text(pDX, IDC_1YEAR_EDIT, m_cs1YearContent);
	DDX_Control(pDX, IDC_3MOUTH_SLIDER, m_csl3MouthSlider);
	DDX_Control(pDX, IDC_5YEAR_SLIDER, m_csl5YearSlider);
	DDX_Control(pDX, IDC_1YEAR_SLIDER, m_csl1YearSlider);
	DDX_Text(pDX, IDC_3MOUTH_DEADLINE_EDIT, m_cs3MouthDeadline);
	DDX_Text(pDX, IDC_1YEAR_DEADLINE_EDIT, m_cs1YearDeadline);
	DDX_Text(pDX, IDC_5YEAR_DEADLINE_EDIT, m_cs5YearDeadline);
}


BEGIN_MESSAGE_MAP(LongPlanDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHANGE_BUTTON, &LongPlanDlg::OnBnClickedSaveButton)
END_MESSAGE_MAP()


// LongPlanDlg ��Ϣ�������


BOOL LongPlanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//������
	m_csl3MouthSlider.SetRange(0, 3);
	m_csl3MouthSlider.SetTicFreq(1);
	m_csl1YearSlider.SetRange(0, 12);
	m_csl1YearSlider.SetTicFreq(1);
	m_csl5YearSlider.SetRange(0, 5);
	m_csl5YearSlider.SetTicFreq(1);
	//��õ�ǰ����
	time_t cur_time = time(0);
	tm *ltm = localtime(&cur_time);
	m_iCurYear = ltm->tm_year + 1900;
	m_iCurMonth = ltm->tm_mon + 1;
	//��ȡ�ļ�
	m_csLPFilePath = m_csLPfFolderPath + _T("\\lp.sch");
	if (PathFileExists(m_csLPFilePath)){
		ReadLPFile(m_csLPFilePath);
	}
	else{
		m_csSinceYear.Format("%d", m_iCurYear);
		m_csSinceMouth.Format("%d", m_iCurMonth);
	}
	ChangeSlider(m_iCurYear, m_iCurMonth);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void LongPlanDlg::ReadLPFile(CString filePath){
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
	//��ȡ��ʼ����
	CString csMsg(pText);
	int n = csMsg.Find("==");
	m_csSinceYear = csMsg.Left(n);
	csMsg.Delete(0, n + 2);
	n = csMsg.Find("==");
	m_csSinceMouth = csMsg.Left(n);
	csMsg.Delete(0, n + 2);
	//��ȡ3���¼ƻ�
	n = csMsg.Find("==");
	m_cs3MouthContent = csMsg.Left(n);
	csMsg.Delete(0, n + 2);
	//��ȡ1��ƻ�
	n = csMsg.Find("==");
	m_cs1YearContent = csMsg.Left(n);
	int length = csMsg.Delete(0, n + 2);
	//��ȡ5��ƻ�
	m_cs5YearContent = csMsg.Right(length);
	UpdateData(false);
}
void LongPlanDlg::OnBnClickedSaveButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CreatMultiDir(m_csLPfFolderPath);
	CFile file;
	if (file.Open(m_csLPFilePath, CFile::modeWrite | CFile::modeCreate) == 0)
	{
		MessageBox(m_csLPFilePath + _T("����ʧ��!"), NULL, MB_ICONEXCLAMATION);
		return;
	}
	CString strSplit = "==";
	//���濪ʼ����
	file.Write(m_csSinceYear, m_csSinceYear.GetLength());
	file.Write(strSplit, strSplit.GetLength());
	file.Write(m_csSinceMouth, m_csSinceMouth.GetLength());
	file.Write(strSplit, strSplit.GetLength());
	//����3���¼ƻ�
	file.Write(m_cs3MouthContent, m_cs3MouthContent.GetLength());
	file.Write(strSplit, strSplit.GetLength());
	//����1��ƻ�
	file.Write(m_cs1YearContent, m_cs1YearContent.GetLength());
	file.Write(strSplit, strSplit.GetLength());
	//����5��ƻ�
	file.Write(m_cs5YearContent, m_cs5YearContent.GetLength());
	file.Flush();
	file.Close();
	ChangeSlider(m_iCurYear, m_iCurMonth);
}
void LongPlanDlg::ChangeSlider(int curYear, int curMouth){
	//����Deadline
	int i3MouthDeadline = _ttoi(m_csSinceMouth) + 3;
	if (i3MouthDeadline == 12){
		i3MouthDeadline = 12;
	}
	else{
		i3MouthDeadline = i3MouthDeadline % 12;
	}
	m_cs3MouthDeadline.Format("%d", i3MouthDeadline);
	int pos = (curMouth - _ttoi(m_csSinceMouth) + 12) % 12;
	if (pos > 3){
		pos = 3;
	}
	else{
		pos = pos;
	}
	m_csl3MouthSlider.SetPos(pos);

	m_cs1YearDeadline.Format("%d", _ttoi(m_csSinceYear)+1);
	if (curYear - _ttoi(m_csSinceYear) >= 1){
		pos = 12;
	}
	else{
		pos = (curMouth - _ttoi(m_csSinceMouth) + 12) % 12;
	}
	m_csl1YearSlider.SetPos(pos);

	m_cs5YearDeadline.Format("%d", _ttoi(m_csSinceYear) + 5);
	if (curYear - _ttoi(m_csSinceYear) >= 5){
		pos = 5;
	}
	else{
		pos = curYear - _ttoi(m_csSinceYear);
	}
	m_csl5YearSlider.SetPos(pos);
	UpdateData(FALSE);
}