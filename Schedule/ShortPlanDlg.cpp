// ShortPlanDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Schedule.h"
#include "ShortPlanDlg.h"
#include "afxdialogex.h"


// ShortPlanDlg 对话框

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


// ShortPlanDlg 消息处理程序
const CString week[] = { "日", "一", "二", "三", "四", "五", "六" };

BOOL ShortPlanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//获得当前日期
	time_t cur_time = time(0);
	tm *ltm = localtime(&cur_time);
	int iDayOfWeek = ltm->tm_wday;
	int iDayOfMonth = ltm->tm_mday;
	m_csDayOfWeek = _T("星期") + week[iDayOfWeek];
	m_csDayOfMonth.Format("%d 号", iDayOfMonth);
	//读取文件内容
	m_csSPFilePath = m_csSPFolderPath + _T("\\sp.sch");
	if (PathFileExists(m_csSPFilePath)){
		ReadLPFile(m_csSPFilePath);
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void ShortPlanDlg::ReadLPFile(CString filePath){
	CFile file;
	if (file.Open(filePath, CFile::modeRead) == 0)
	{
		MessageBox(filePath + "读取文件失败!", NULL, MB_ICONEXCLAMATION);
		return;
	}
	int size = file.GetLength();
	char* pText = new char[size + 1];
	int nRet = file.Read(pText, size);
	file.Close();
	pText[nRet] = 0;
	//读入周计划
	CString csMsg(pText);
	int n = csMsg.Find("==");
	m_csWeeklyPlanContent = csMsg.Left(n);
	//读入月计划
	int length = csMsg.Delete(0, n + 2);
	m_csMonthlyPlanContent = csMsg.Right(length);
	UpdateData(false);
}
void ShortPlanDlg::OnBnClickedSaveButton()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CreatMultiDir(m_csSPFolderPath);
	CFile file;
	if (file.Open(m_csSPFilePath, CFile::modeWrite | CFile::modeCreate) == 0)
	{
		MessageBox(m_csSPFilePath + _T("保存失败!"), NULL, MB_ICONEXCLAMATION);
		return;
	}
	CString strSplit = "==";
	//写入周计划
	file.Write(m_csWeeklyPlanContent, m_csWeeklyPlanContent.GetLength());
	file.Write(strSplit, strSplit.GetLength());
	//写入月计划
	file.Write(m_csMonthlyPlanContent, m_csMonthlyPlanContent.GetLength());
	file.Flush();
	file.Close();
}
