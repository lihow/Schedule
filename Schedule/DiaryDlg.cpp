// DiaryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Schedule.h"
#include "DiaryDlg.h"
#include "afxdialogex.h"


// DiaryDlg �Ի���

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


// DiaryDlg ��Ϣ�������


BOOL DiaryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��������
	font.CreatePointFont(100, _T("����"));     //ѡ������
	m_ceDiaryContent.SetFont(&font);
	//�����ռ�
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
	//�������
	time_t cur_time = time(0);
	tm *ltm = localtime(&cur_time);
	m_csCurYear.Format("%d", ltm->tm_year+1900);
	m_csCurMonth.Format("%d", ltm->tm_mon+1);
	m_csCurDay.Format("%d", ltm->tm_mday);
	m_csDate = m_csCurYear + _T("��") + m_csCurMonth + _T("��") + m_csCurDay + _T("��");
	m_csWeather = _T("��");
	//��ȡ���е��ռǣ�����ʾ 
	m_csDiaryfloderPath = m_csDiaryPath + _T("/") + m_csCurYear + _T("/") + m_csCurMonth + _T("/");
	m_csDiaryFileName = m_csDiaryfloderPath + m_csCurDay + _T(".sch");
	if (PathFileExists(m_csDiaryFileName)){
		ReadDiary(m_csDiaryFileName);
	}
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void DiaryDlg::ReadDiary(CString csDiaryFile){
	
	CFile file;
	if (file.Open(csDiaryFile, CFile::modeRead) == 0)
	{
		MessageBox(csDiaryFile + "��ȡ�ļ�ʧ��!", NULL, MB_ICONEXCLAMATION);
		return;
	}
	int size = file.GetLength();
	char* pText = new char[size + 1];
	int nRet = file.Read(pText, size);
	file.Close();
	pText[nRet] = 0;
	//��ȡ���ں�������Ϣ
	CString csMsg(pText);
	int n = csMsg.Find("==");
	m_csDate = csMsg.Left(n);
	csMsg.Delete(0, n + 2);
	n = csMsg.Find("==");
	m_csWeather = csMsg.Left(n);
	//��ȡ�ռ�����
	int length = csMsg.Delete(0, n + 2);
	m_csContent = csMsg.Right(length);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_DIARY_EDIT);
	pEdit->SetWindowText(m_csContent);
	//m_ceDiaryContent.LineScroll(m_ceDiaryContent.GetLineCount());ת�����һ��
	UpdateData(false);
	pText = NULL;
	delete pText;
}
void DiaryDlg::OnBnClickedSaveButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CreatMultiDir(m_csDiaryfloderPath);
	//�����ռ�ͷ��Ϣ
	UpdateData(true);
	CString strText;
	GetDlgItemText(IDC_DIARY_EDIT, strText);
	if (strText == "" && m_csWeather == "��"){//����Ϊ�գ�������
		return;
	}

	CFile file;
	if (file.Open(m_csDiaryFileName, CFile::modeWrite | CFile::modeCreate) == 0)
	{
		MessageBox(m_csDiaryFileName + _T("����ʧ��!"), NULL, MB_ICONEXCLAMATION);
		return;
	}

	//�����ռ�ͷ��Ϣ
	CString strSplit = "==";
	file.Write(m_csDate, m_csDate.GetLength());
	file.Write(strSplit, strSplit.GetLength());
	file.Write(m_csWeather, m_csWeather.GetLength());
	file.Write(strSplit, strSplit.GetLength());
	//�����ռ�����
	file.Write(strText, strText.GetLength());
	file.Flush();
	file.Close();
	//MessageBox(m_csDiaryFileName + _T("����ɹ�!"), NULL, MB_ICONEXCLAMATION);

	//ˢ���б�
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
	//�����չ��
	TVSORTCB tvsortcb;
	tvsortcb.hParent = root;
	tvsortcb.lpfnCompare = SortByFileName;
	tvsortcb.lParam = (LPARAM)&m_ctDiraiesTree;
	m_ctDiraiesTree.SortChildrenCB(&tvsortcb);
	//m_ctDiraiesTree.Expand(root, TVE_EXPAND);
}

void DiaryDlg::OnNMClickDiraiesTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		if (hParentItem == NULL)//û�и��ڵ�
		{
			ItemPath = m_ctDiraiesTree.GetItemText(CurrentItem);
			ItemPath = ItemPath + TemPath;

			break;
		}
		else//�и��ڵ�
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedSaveButton();
	GetDlgItem(IDC_DIARY_EDIT)->SetWindowText(_T(""));
	m_csDiaryFileName = m_csDiaryfloderPath + m_csCurDay + _T(".sch");
	m_csDate = m_csCurYear + _T("��") + m_csCurMonth + _T("��") + m_csCurDay + _T("��");
	m_csWeather = _T("��");
	if (PathFileExists(m_csDiaryFileName)){
		ReadDiary(m_csDiaryFileName);
	}
	UpdateData(FALSE);
}
