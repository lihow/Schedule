#pragma once
#include <time.h>
#include"public.h"
#include "afxcmn.h"

// LongPlanDlg �Ի���

class LongPlanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LongPlanDlg)

public:
	LongPlanDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LongPlanDlg();

// �����ļ�
	CString m_csLPfFolderPath = rootFolder + _T("lp");
	CString m_csLPFilePath;
	void ReadLPFile(CString filePath);
// ��ǰʱ��
	int  m_iCurYear;
	int  m_iCurMonth;
	void ChangeSlider(int curYear, int curMouth);

// �Ի�������
	enum { IDD = IDD_LONG_PLAN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSaveButton();
	CString m_csSinceYear;
	CString m_csSinceMouth;
	CString m_cs3MouthContent;
	CString m_cs5YearContent;
	CString m_cs1YearContent;
	CSliderCtrl m_csl3MouthSlider;
	CSliderCtrl m_csl5YearSlider;
	CSliderCtrl m_csl1YearSlider;
	CString m_cs3MouthDeadline;
	CString m_cs1YearDeadline;
	CString m_cs5YearDeadline;
};
