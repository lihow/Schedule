
// ScheduleDlg.h : 头文件
//

#pragma once
#include"EventDlg.h"
#include"ShortPlanDlg.h"
#include"LongPlanDlg.h"
#include"WantToBeDlg.h"
#include"DiaryDlg.h"
#include"LoginDlg.h"
// CScheduleDlg 对话框
class CScheduleDlg : public CDialogEx
{
// 构造
public:
	CScheduleDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CScheduleDlg();
// 对话框数据
	enum { IDD = IDD_SCHEDULE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
// 其他窗口
	BOOL m_iMainType = 0;	//main interface type
	CRect m_rectWorkspace;
	EventDlg* m_dlgEvent;
	ShortPlanDlg* m_dlgShortPlan;
	LongPlanDlg* m_dlgLongPlan;
	WantToBeDlg* m_dlgWTb;
	DiaryDlg* m_dlgDiary;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedShortPlan();
	afx_msg void OnBnClickedSchedule();

// 窗口处理函数
	void CloseWorkSpaceWindow(int window_id);
	afx_msg void OnBnClickedLongPlan();
	afx_msg void OnBnClickedWantToBe();
	afx_msg void OnBnClickedDiary();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_csNowTime;
};
