// DiaryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Schedule.h"
#include "DiaryDlg.h"
#include "afxdialogex.h"


// DiaryDlg 对话框

IMPLEMENT_DYNAMIC(DiaryDlg, CDialogEx)

DiaryDlg::DiaryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DiaryDlg::IDD, pParent)
	, m_csDate(_T(""))
	, m_csWeather(_T(""))
{

}

DiaryDlg::~DiaryDlg()
{
	OnBnClickedSaveButton();
}

void DiaryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DIARY_EDIT, m_ceDiaryContent);
	DDX_Text(pDX, IDC_DATE_EDIT, m_csDate);
	DDX_Text(pDX, IDC_WEATHER_EDIT, m_csWeather);
	DDX_Control(pDX, IDC_DIRAIES_TREE, m_ctDiraiesTree);
}


BEGIN_MESSAGE_MAP(DiaryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &DiaryDlg::OnBnClickedSaveButton)
	ON_NOTIFY(NM_CLICK, IDC_DIRAIES_TREE, &DiaryDlg::OnNMClickDiraiesTree)
	ON_BN_CLICKED(IDC_OPEN_DIARY_BUTTON, &DiaryDlg::OnBnClickedOpenDiaryButton)
	ON_BN_CLICKED(IDC_TODAY_DIARY_BUTTON, &DiaryDlg::OnBnClickedTodayDiaryButton)
END_MESSAGE_MAP()


// DiaryDlg 消息处理程序


BOOL DiaryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//字体设置
	font.CreatePointFont(100, _T("宋体"));     //选择字体
	m_ceDiaryContent.SetFont(&font);
	//加载日记
	m_imageLIst.Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 0);
	m_imageLIst.SetBkColor(RGB(255, 255, 255));
	m_ctDiraiesTree.SetImageList(&m_imageLIst, TVSIL_NORMAL);
	HTREEITEM hRoot;
	m_ctDiraiesTree.DeleteAllItems();
	SHGetFileInfo(m_csDiaryPath, 0, &fileinfo, sizeof(fileinfo), SHGFI_USEFILEATTRIBUTES | SHGFI_SYSICONINDEX | SHGFI_ICON);
	index = m_imageLIst.Add(fileinfo.hIcon);
	hRoot = m_ctDiraiesTree.InsertItem(m_csDiaryPath, index, index, TVI_ROOT);
	LoadDiary(hRoot, m_csDiaryPath);
	m_ctDiraiesTree.Expand(hRoot, TVE_EXPAND);
	//获得日期
	time_t cur_time = time(0);
	tm *ltm = localtime(&cur_time);
	m_csCurYear.Format("%d", ltm->tm_year+1900);
	m_csCurMonth.Format("%d", ltm->tm_mon+1);
	m_csCurDay.Format("%d", ltm->tm_mday);
	m_csDate = m_csCurYear + _T("年") + m_csCurMonth + _T("月") + m_csCurDay + _T("日");
	m_csWeather = _T("无");
	//读取已有的日记，并显示 
	m_csDiaryfloderPath = m_csDiaryPath + _T("/") + m_csCurYear + _T("/") + m_csCurMonth + _T("/");
	m_csDiaryFileName = m_csDiaryfloderPath + m_csCurDay + _T(".sch");
	if (PathFileExists(m_csDiaryFileName)){
		ReadDiary(m_csDiaryFileName);
	}
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void DiaryDlg::ReadDiary(CString csDiaryFile){
	
	CFile file;
	if (file.Open(csDiaryFile, CFile::modeRead) == 0)
	{
		MessageBox(csDiaryFile + "读取文件失败!", NULL, MB_ICONEXCLAMATION);
		return;
	}
	int size = file.GetLength();
	char* pText = new char[size + 1];
	int nRet = file.Read(pText, size);
	file.Close();
	pText[nRet] = 0;
	//读取日期和天气信息
	CString csMsg(pText);
	int n = csMsg.Find("==");
	m_csDate = csMsg.Left(n);
	csMsg.Delete(0, n + 2);
	n = csMsg.Find("==");
	m_csWeather = csMsg.Left(n);
	//读取日记内容
	int length = csMsg.Delete(0, n + 2);
	m_csContent = csMsg.Right(length);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_DIARY_EDIT);
	pEdit->SetWindowText(m_csContent);
	//m_ceDiaryContent.LineScroll(m_ceDiaryContent.GetLineCount());转到最后一行
	UpdateData(false);
	pText = NULL;
	delete pText;
}
void DiaryDlg::OnBnClickedSaveButton()
{
	// TODO:  在此添加控件通知处理程序代码
	CreatMultiDir(m_csDiaryfloderPath);
	//保存日记头信息
	UpdateData(true);
	CString strText;
	GetDlgItemText(IDC_DIARY_EDIT, strText);
	if (strText == "" && m_csWeather == "无"){//内容为空，不保存
		return;
	}

	CFile file;
	if (file.Open(m_csDiaryFileName, CFile::modeWrite | CFile::modeCreate) == 0)
	{
		MessageBox(m_csDiaryFileName + _T("保存失败!"), NULL, MB_ICONEXCLAMATION);
		return;
	}

	//保存日记头信息
	CString strSplit = "==";
	file.Write(m_csDate, m_csDate.GetLength());
	file.Write(strSplit, strSplit.GetLength());
	file.Write(m_csWeather, m_csWeather.GetLength());
	file.Write(strSplit, strSplit.GetLength());
	//保存日记内容
	file.Write(strText, strText.GetLength());
	file.Flush();
	file.Close();
	//MessageBox(m_csDiaryFileName + _T("保存成功!"), NULL, MB_ICONEXCLAMATION);

	//刷新列表
	HTREEITEM hRoot;
	m_ctDiraiesTree.DeleteAllItems();
	SHGetFileInfo(m_csDiaryPath, 0, &fileinfo, sizeof(fileinfo), SHGFI_USEFILEATTRIBUTES | SHGFI_SYSICONINDEX | SHGFI_ICON);
	index = m_imageLIst.Add(fileinfo.hIcon);
	hRoot = m_ctDiraiesTree.InsertItem(m_csDiaryPath, index, index, TVI_ROOT);
	LoadDiary(hRoot, m_csDiaryPath);
	m_ctDiraiesTree.Expand(hRoot, TVE_EXPAND);
	UpdateData(false);
}
int CALLBACK SortByFileName(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	CTreeCtrl * pTree = (CTreeCtrl *)lParamSort;
	HTREEITEM hItem1 = (HTREEITEM)lParam1;
	HTREEITEM hItem2 = (HTREEITEM)lParam2;
	CString strItem1 = pTree->GetItemText(hItem1);
	int loc1 = strItem1.Find(".sch");
	int iItem1 = _ttoi(strItem1.Left(loc1));
	CString  strItem2 = pTree->GetItemText(hItem2);
	int loc2 = strItem2.Find(".sch");
	int iItem2 = _ttoi(strItem2.Left(loc1));
	return iItem1 > iItem2;
}
void DiaryDlg::LoadDiary(HTREEITEM root, CString path){
	CFileFind finder;
	HTREEITEM hFatherItem, hSonItem;
	BOOL exit = finder.FindFile(path + _T("\\*.*"));
	while (exit){
		exit = finder.FindNextFile();
		if (finder.IsDirectory() && !finder.IsDots()){
			CString mDir = finder.GetFileTitle();
			SHGetFileInfo(finder.GetFilePath(), 0, &fileinfo, sizeof(fileinfo), SHGFI_ICON);
			index = m_imageLIst.Add(fileinfo.hIcon);
			hFatherItem = m_ctDiraiesTree.InsertItem(mDir, index, index, root, TVI_LAST);

			m_ctDiraiesTree.SetItemData(hFatherItem, (DWORD)hFatherItem);

			mDir = path + _T("\\") + mDir;
			LoadDiary(hFatherItem, mDir);
		}
		else if (!finder.IsDirectory() && !finder.IsDots()){
			CString mDir = finder.GetFileName();
			SHGetFileInfo(mDir, 0, &fileinfo, sizeof(fileinfo), SHGFI_USEFILEATTRIBUTES | SHGFI_SYSICONINDEX | SHGFI_ICON);
			index = m_imageLIst.Add(fileinfo.hIcon);
			hSonItem = m_ctDiraiesTree.InsertItem(mDir, index, index, root, TVI_LAST);

			m_ctDiraiesTree.SetItemData(hSonItem, (DWORD)hSonItem);
		}
	}
	finder.Close();	
	//排序和展开
	TVSORTCB tvsortcb;
	tvsortcb.hParent = root;
	tvsortcb.lpfnCompare = SortByFileName;
	tvsortcb.lParam = (LPARAM)&m_ctDiraiesTree;
	m_ctDiraiesTree.SortChildrenCB(&tvsortcb);
	//m_ctDiraiesTree.Expand(root, TVE_EXPAND);
}

void DiaryDlg::OnNMClickDiraiesTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	CPoint point;
	GetCursorPos(&point);
	m_ctDiraiesTree.ScreenToClient(&point);
	UINT uFlags;
	HTREEITEM CurrentItem;
	CurrentItem = m_ctDiraiesTree.HitTest(point, &uFlags);

	CString ItemPath;
	ItemPath.Empty();
	CString TemPath(_T(""));
	while (TRUE)
	{
		HTREEITEM hParentItem = m_ctDiraiesTree.GetParentItem(CurrentItem);
		if (hParentItem == NULL)//没有父节点
		{
			ItemPath = m_ctDiraiesTree.GetItemText(CurrentItem);
			ItemPath = ItemPath + TemPath;

			break;
		}
		else//有父节点
		{
			TemPath = _T("\\") + m_ctDiraiesTree.GetItemText(CurrentItem) + TemPath;
			CurrentItem = m_ctDiraiesTree.GetParentItem(CurrentItem);
		}
	}
	m_csClickTreeName = ItemPath;
	if (m_csClickTreeName.Find(_T(".sch")) != -1){
		GetDlgItem(IDC_OPEN_DIARY_BUTTON)->EnableWindow(TRUE);
	}
	else{
		GetDlgItem(IDC_OPEN_DIARY_BUTTON)->EnableWindow(FALSE);
	}
	*pResult = 0;
}


void DiaryDlg::OnBnClickedOpenDiaryButton()
{
	// TODO:  在此添加控件通知处理程序代码
	OnBnClickedSaveButton();
	GetDlgItem(IDC_DIARY_EDIT)->SetWindowText(_T(""));
	m_csDiaryFileName = m_csClickTreeName;
	if (PathFileExists(m_csDiaryFileName)){
		ReadDiary(m_csDiaryFileName);
	}
	GetDlgItem(IDC_OPEN_DIARY_BUTTON)->EnableWindow(FALSE);
}


void DiaryDlg::OnBnClickedTodayDiaryButton()
{
	// TODO:  在此添加控件通知处理程序代码
	OnBnClickedSaveButton();
	GetDlgItem(IDC_DIARY_EDIT)->SetWindowText(_T(""));
	m_csDiaryFileName = m_csDiaryfloderPath + m_csCurDay + _T(".sch");
	m_csDate = m_csCurYear + _T("年") + m_csCurMonth + _T("月") + m_csCurDay + _T("日");
	m_csWeather = _T("无");
	if (PathFileExists(m_csDiaryFileName)){
		ReadDiary(m_csDiaryFileName);
	}
	UpdateData(FALSE);
}
