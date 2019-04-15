
// ScheduleDlg.h : ͷ�ļ�
//

#pragma once
#include"EventDlg.h"
#include"ShortPlanDlg.h"
#include"LongPlanDlg.h"
#include"WantToBeDlg.h"
#include"DiaryDlg.h"
#include"LoginDlg.h"
// CScheduleDlg �Ի���
class CScheduleDlg : public CDialogEx
{
// ����
public:
	CScheduleDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CScheduleDlg();
// �Ի�������
	enum { IDD = IDD_SCHEDULE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
// ��������
	BOOL m_iMainType = 0;	//main interface type
	CRect m_rectWorkspace;
	EventDlg* m_dlgEvent;
	ShortPlanDlg* m_dlgShortPlan;
	LongPlanDlg* m_dlgLongPlan;
	WantToBeDlg* m_dlgWTb;
	DiaryDlg* m_dlgDiary;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedShortPlan();
	afx_msg void OnBnClickedSchedule();

// ���ڴ�����
	void CloseWorkSpaceWindow(int window_id);
	afx_msg void OnBnClickedLongPlan();
	afx_msg void OnBnClickedWantToBe();
	afx_msg void OnBnClickedDiary();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_csNowTime;
};
