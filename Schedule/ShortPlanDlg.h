#pragma once
#include <time.h>
#include"public.h"

// ShortPlanDlg �Ի���

class ShortPlanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShortPlanDlg)
public:
	ShortPlanDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ShortPlanDlg();
// �����ļ�
	CString m_csSPFolderPath = rootFolder + _T("sp");
	CString m_csSPFilePath;
	void ReadLPFile(CString filePath);
// �Ի�������
	enum { IDD = IDD_SHORT_PLAN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSaveButton();
	CString m_csDayOfWeek;
	CString m_csDayOfMonth;
	CString m_csWeeklyPlanContent;
	CString m_csMonthlyPlanContent;
};
