
// ScheduleDlg.cpp : ʵ���ļ�
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
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CScheduleDlg �Ի���



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


// CScheduleDlg ��Ϣ�������

BOOL CScheduleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	SetTimer(1, 1000, NULL);//ʱ��
	//��¼
	LoginDlg loginDlg;
	if (loginDlg.DoModal() != IDOK){
		EndDialog(-1);
	}
	else{
		OnBnClickedSchedule();//�¼�����
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CScheduleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CTime t1;
	t1 = CTime::GetCurrentTime();//��ȡ��ǰϵͳʱ��
	m_csNowTime.Format("%d/%d/%d %d:%02d", t1.GetYear(), t1.GetMonth(), t1.GetDay(), t1.GetHour(), t1.GetMinute());
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}
