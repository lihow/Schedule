
// ScheduleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Schedule.h"
#include "ScheduleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define EVENT_DLG		1
#define SHORT_PLAN_DLG	2
#define LONG_PLAN_DLG   3
#define WANT_TO_BE_DLG  4
#define DIARY_DLG       5
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CScheduleDlg 对话框



CScheduleDlg::CScheduleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScheduleDlg::IDD, pParent)
	, m_csNowTime(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CScheduleDlg::~CScheduleDlg(){
	//KillTimer(1);
}
void CScheduleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TIME_EDIT, m_csNowTime);
}

BEGIN_MESSAGE_MAP(CScheduleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SHORT_PLAN, &CScheduleDlg::OnBnClickedShortPlan)
	ON_BN_CLICKED(IDC_SCHEDULE, &CScheduleDlg::OnBnClickedSchedule)
	ON_BN_CLICKED(IDC_LONG_PLAN, &CScheduleDlg::OnBnClickedLongPlan)
	ON_BN_CLICKED(IDC_WANT_TO_BE, &CScheduleDlg::OnBnClickedWantToBe)
	ON_BN_CLICKED(IDC_DIARY, &CScheduleDlg::OnBnClickedDiary)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CScheduleDlg 消息处理程序

BOOL CScheduleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	SetTimer(1, 1000, NULL);//时间
	//登录
	LoginDlg loginDlg;
	if (loginDlg.DoModal() != IDOK){
		EndDialog(-1);
	}
	else{
		OnBnClickedSchedule();//事件界面
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CScheduleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CScheduleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CScheduleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CScheduleDlg::CloseWorkSpaceWindow(int window_id){
	switch (window_id){
	case EVENT_DLG:
		m_dlgEvent->ShowWindow(SW_HIDE);
		delete m_dlgEvent;
		break;
	case SHORT_PLAN_DLG:
		m_dlgShortPlan->ShowWindow(SW_HIDE);
		delete m_dlgShortPlan;
		break;
	case LONG_PLAN_DLG:
		m_dlgLongPlan->ShowWindow(SW_HIDE);
		delete m_dlgLongPlan;
		break;
	case WANT_TO_BE_DLG:
		m_dlgWTb->ShowWindow(SW_HIDE);
		delete m_dlgWTb;
		break;
	case DIARY_DLG:
		m_dlgDiary->ShowWindow(SW_HIDE);
		delete m_dlgDiary;
		break;
	default:
		return;
	}
}

void CScheduleDlg::OnBnClickedSchedule()
{
	// TODO:  在此添加控件通知处理程序代码
	CloseWorkSpaceWindow(m_iMainType);
	m_iMainType = EVENT_DLG;
	GetDlgItem(IDC_WORKSPACE)->ShowWindow(false);
	m_dlgEvent = new EventDlg();
	m_dlgEvent->Create(IDD_EVENT_DIALOG);
	GetDlgItem(IDC_WORKSPACE)->GetWindowRect(&m_rectWorkspace);
	ScreenToClient(&m_rectWorkspace);
	m_dlgEvent->MoveWindow(&m_rectWorkspace, TRUE);
	m_dlgEvent->ShowWindow(SW_SHOW);
}


void CScheduleDlg::OnBnClickedShortPlan()
{
	// TODO:  在此添加控件通知处理程序代码
	CloseWorkSpaceWindow(m_iMainType);
	m_iMainType = SHORT_PLAN_DLG;
	GetDlgItem(IDC_WORKSPACE)->ShowWindow(false);
	m_dlgShortPlan = new ShortPlanDlg();
	m_dlgShortPlan->Create(IDD_SHORT_PLAN_DIALOG);
	GetDlgItem(IDC_WORKSPACE)->GetWindowRect(&m_rectWorkspace);
	ScreenToClient(&m_rectWorkspace);
	m_dlgShortPlan->MoveWindow(&m_rectWorkspace, TRUE);
	m_dlgShortPlan->ShowWindow(SW_SHOW);
}




void CScheduleDlg::OnBnClickedLongPlan()
{
	// TODO:  在此添加控件通知处理程序代码
	CloseWorkSpaceWindow(m_iMainType);
	m_iMainType = LONG_PLAN_DLG;
	GetDlgItem(IDC_WORKSPACE)->ShowWindow(false);
	m_dlgLongPlan = new LongPlanDlg();
	m_dlgLongPlan->Create(IDD_LONG_PLAN_DIALOG);
	GetDlgItem(IDC_WORKSPACE)->GetWindowRect(&m_rectWorkspace);
	ScreenToClient(&m_rectWorkspace);
	m_dlgLongPlan->MoveWindow(&m_rectWorkspace, TRUE);
	m_dlgLongPlan->ShowWindow(SW_SHOW);
}


void CScheduleDlg::OnBnClickedWantToBe()
{
	// TODO:  在此添加控件通知处理程序代码
	CloseWorkSpaceWindow(m_iMainType);
	m_iMainType = WANT_TO_BE_DLG;
	GetDlgItem(IDC_WORKSPACE)->ShowWindow(false);
	m_dlgWTb = new WantToBeDlg();
	m_dlgWTb->Create(IDD_WANT_TO_BE_DIALOG);
	GetDlgItem(IDC_WORKSPACE)->GetWindowRect(&m_rectWorkspace);
	ScreenToClient(&m_rectWorkspace);
	m_dlgWTb->MoveWindow(&m_rectWorkspace, TRUE);
	m_dlgWTb->ShowWindow(SW_SHOW);
}


void CScheduleDlg::OnBnClickedDiary()
{
	// TODO:  在此添加控件通知处理程序代码
	CloseWorkSpaceWindow(m_iMainType);
	m_iMainType = DIARY_DLG;
	GetDlgItem(IDC_WORKSPACE)->ShowWindow(false);
	m_dlgDiary = new DiaryDlg();
	m_dlgDiary->Create(IDD_DIARY_DIALOG);
	GetDlgItem(IDC_WORKSPACE)->GetWindowRect(&m_rectWorkspace);
	ScreenToClient(&m_rectWorkspace);
	m_dlgDiary->MoveWindow(&m_rectWorkspace, TRUE);
	m_dlgDiary->ShowWindow(SW_SHOW);
}


void CScheduleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CTime t1;
	t1 = CTime::GetCurrentTime();//获取当前系统时间
	m_csNowTime.Format("%d/%d/%d %d:%02d", t1.GetYear(), t1.GetMonth(), t1.GetDay(), t1.GetHour(), t1.GetMinute());
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}
