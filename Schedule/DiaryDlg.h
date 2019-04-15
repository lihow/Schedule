#pragma once
#include "afxwin.h"
#include <time.h>
#include "public.h"
#include "afxcmn.h"
// DiaryDlg 对话框

class DiaryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DiaryDlg)

public:
	DiaryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DiaryDlg();
// 存放位置
	CString m_csDiaryFileName;
	CString m_csDiaryPath = rootFolder + _T("diary");
	CString m_csDiaryfloderPath;
	void ReadDiary(CString csDiaryFile);
	void LoadDiary(HTREEITEM root, CString path);
//日期
	CString  m_csCurYear;
	CString  m_csCurMonth;
	CString  m_csCurDay;
// 对话框数据
	enum { IDD = IDD_DIARY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSaveButton();
	CEdit m_ceDiaryContent;
	CString m_csDate;
	CString m_csWeather;
	CString m_csContent;
	CTreeCtrl m_ctDiraiesTree;
	CImageList m_imageLIst;
	SHFILEINFO fileinfo;
	int index;
	afx_msg void OnNMClickDiraiesTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOpenDiaryButton();
	afx_msg void OnBnClickedTodayDiaryButton();
	CString m_csClickTreeName;
	CFont font;
};
