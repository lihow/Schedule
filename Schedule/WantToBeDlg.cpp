// WantToBeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Schedule.h"
#include "WantToBeDlg.h"
#include "afxdialogex.h"


// WantToBeDlg 对话框

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


// WantToBeDlg 消息处理程序


BOOL WantToBeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  在此添加额外的初始化
	//字体设置
	CEdit* m_edWTBContent = (CEdit *)GetDlgItem(IDC_WANT_TO_BE_EDIT);
	CEdit* m_edNowContent = (CEdit *)GetDlgItem(IDC_NOW_ME_EDIT);
	font.CreatePointFont(130, _T("隶书"));     //选择字体
	m_edWTBContent->SetFont(&font);
	m_edNowContent->SetFont(&font);

	m_csWTBFilePath = m_csWTBFolderPath + _T("\\wtb.sch");
	if (PathFileExists(m_csWTBFilePath)){
		readWTBFile(m_csWTBFilePath);
	}
	else{
		m_csWTBContent = _T("加油！：-）");
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
void WantToBeDlg::readWTBFile(CString filePath){
	CFile file;
	if (file.Open(filePath, CFile::modeRead) == 0)
	{
		MessageBox("读取文件失败!", NULL, MB_ICONEXCLAMATION);
		return;
	}
	int size = file.GetLength();
	char* pText = new char[size + 1];
	int nRet = file.Read(pText, size);
	file.Close();
	pText[nRet] = 0;
	//读取“想成为的人”
	CString csMsg(pText);
	int n = csMsg.Find("==");
	m_csWTBContent = csMsg.Left(n);
	//读取“现在”
	int length = csMsg.Delete(0, n + 2);
	m_csNowContent = csMsg.Right(length);
	UpdateData(FALSE);
}
void WantToBeDlg::OnBnClickedSaveButton()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CreatMultiDir(m_csWTBFolderPath);
	CFile file;
	if (file.Open(m_csWTBFilePath, CFile::modeWrite | CFile::modeCreate) == 0)
	{
		MessageBox(m_csWTBFilePath + _T("保存失败!"), NULL, MB_ICONEXCLAMATION);
		return;
	}
	//保存“想成为的人”
	CString strSplit = "==";
	file.Write(m_csWTBContent, m_csWTBContent.GetLength());
	file.Write(strSplit, strSplit.GetLength());//分割符
	//保存“现在”
	file.Write(m_csNowContent, m_csNowContent.GetLength());
	file.Flush();
	file.Close();

	m_csSaveStatus = "=>";
	UpdateData(FALSE);
}
