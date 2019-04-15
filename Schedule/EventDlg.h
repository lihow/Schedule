#pragma once
#include "afxwin.h"
#include <time.h>
#include"public.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include<vector>
using namespace std;

// EventDlg �Ի���

class EventDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EventDlg)

public:
	EventDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~EventDlg();
//�¼�����
	CString m_csEventfFolderPath = rootFolder + _T("ev");
	CString m_csEventFilePathToday;
	CString m_csEventFilePathTomorrow;
	CString m_csEventFilePathDayAfter;
	CString m_csEventFilePathSelect;
	void ReadEventFile(CString filePath);
	int m_iSelect;
	void LoadEventFile(CString folderpath);
	vector<vector<int>> m_ivecEvents;
	void ReFreshCalendar(int findMonth);
// ��ǰ����
	int m_iCurYear;
	int m_iCurMonth;
	int m_iDayOfWeek;
	int m_iDayOfMonth;
	CString m_csYear;
	CString m_csMonth;
	CString m_csDay;
//��ť����
	void showEventButton(bool isShow);
//������ͼ
	void DrawYearCalendar(CDC *pDc, CRect rect);

// �Ի�������
	enum { IDD = IDD_EVENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedMonthCalendarButton();
	afx_msg void OnBnClickedYearCalendarButton();
	CString m_csEventContent;
	afx_msg void OnBnClickedTomorrowButton();
	afx_msg void OnBnClickedTodayButton();
	afx_msg void OnBnClickedDayAfterTomButton();
	afx_msg void OnBnClickedSaveButton();
	afx_msg void OnMcnSelchangeMonthcalendar(NMHDR *pNMHDR, LRESULT *pResult);
	CMonthCalCtrl m_cmMonthControl;
};
