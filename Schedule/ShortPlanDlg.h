#pragma once
#include <time.h>
#include"public.h"

// ShortPlanDlg 对话框

class ShortPlanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShortPlanDlg)
public:
	ShortPlanDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ShortPlanDlg();
// 保存文件
	CString m_csSPFolderPath = rootFolder + _T("sp");
	CString m_csSPFilePath;
	void ReadLPFile(CString filePath);
// 对话框数据
	enum { IDD = IDD_SHORT_PLAN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSaveButton();
	CString m_csDayOfWeek;
	CString m_csDayOfMonth;
	CString m_csWeeklyPlanContent;
	CString m_csMonthlyPlanContent;
};
