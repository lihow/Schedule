// EventDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Schedule.h"
#include "EventDlg.h"
#include "afxdialogex.h"


// EventDlg �Ի���

IMPLEMENT_DYNAMIC(EventDlg, CDialogEx)

EventDlg::EventDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(EventDlg::IDD, pParent)
	, m_csEventContent(_T(""))
{

}

EventDlg::~EventDlg()
{
}

void EventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EVENT_CONTENT_EDIT, m_csEventContent);
	DDX_Control(pDX, IDC_MONTHCALENDAR, m_cmMonthControl);
}


BEGIN_MESSAGE_MAP(EventDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MONTH_CALENDAR_BUTTON, &EventDlg::OnBnClickedMonthCalendarButton)
	ON_BN_CLICKED(IDC_YEAR_CALENDAR_BUTTON, &EventDlg::OnBnClickedYearCalendarButton)
	ON_BN_CLICKED(IDC_TOMORROW_BUTTON, &EventDlg::OnBnClickedTomorrowButton)
	ON_BN_CLICKED(IDC_TODAY_BUTTON, &EventDlg::OnBnClickedTodayButton)
	ON_BN_CLICKED(IDC_DAY_AFTER_TOM_BUTTON, &EventDlg::OnBnClickedDayAfterTomButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &EventDlg::OnBnClickedSaveButton)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR, &EventDlg::OnMcnSelchangeMonthcalendar)
END_MESSAGE_MAP()

const CString months[] = { "1 ��", "2 ��", "3 ��", "4 ��", "5 ��", "6 ��", "7 ��", "8 ��", \
"9 ��", "10��", "11��", "12��" };
const int dayOfMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
#define TODAY 0
#define TOMORROW 1
#define DAYAFTER 2
#define SELECT 3
// EventDlg ��Ϣ�������
void EventDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


BOOL EventDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��õ�ǰ����
	time_t cur_time = time(0);
	tm *ltm = localtime(&cur_time);
	m_iCurYear = ltm->tm_year + 1900;
	m_iCurMonth = ltm->tm_mon + 1;
	m_iDayOfWeek = ltm->tm_wday;
	m_iDayOfMonth = ltm->tm_mday;
	//�¼��ļ�
	CString yearFolder;
	yearFolder.Format("%d", m_iCurYear);
	m_csEventfFolderPath = m_csEventfFolderPath + _T("\\") + yearFolder;//��ȡ������¼�
	LoadEventFile(m_csEventfFolderPath);
	OnBnClickedTodayButton();
	//�¼��Ӵ�
	ReFreshCalendar(m_iCurMonth - 1);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
void EventDlg::OnBnClickedMonthCalendarButton()
{
	CRect Rect;
	GetDlgItem(IDC_TEMP_STATIC)->GetClientRect(&Rect);
	CDC* pDc = this->GetDC();
	InvalidateRect(&Rect);//��cr_DrawRect�������ػ�
	GetDlgItem(IDC_TEMP_STATIC)->ShowWindow(FALSE);
	UpdateWindow();
	showEventButton(TRUE);
}
void EventDlg::DrawYearCalendar(CDC *pDc, CRect rect){
	int calendarLeft = 11;
	int calendarTop = 11;
	int calendarRight = rect.Width();
	int calendarButtom = rect.Height();
	pDc->Rectangle(calendarLeft, calendarTop, calendarRight, calendarButtom);
	int partWidth = (calendarRight - calendarLeft) / 20;
	int partHeight = (calendarButtom - calendarTop) / 20;
	int year = m_iCurYear;
	int month = m_iCurMonth;
	int nowDay = m_iDayOfMonth;
	//�������� 1���� ����
	for (int i = 1, row = 0, col = 0; i <= 12; i++){
		pDc->SetTextColor(RGB(125, 0, 255));
		if (18 < col){
			col = 0;
			row++;
		}
		pDc->TextOut(calendarLeft + partWidth*col+3, calendarTop + partHeight * row+2, _T(" ")+months[i - 1]);
		col+=2;
		int daysOfMonth = 0;
		if (2 == i){
			if ((year % 4 == 0 && year % 100) || (year % 400 == 0)){
				daysOfMonth = 29;
			}
			else{
				daysOfMonth = 28;
			}
		}
		else if (1 == i || 3 == i || 5 == i || 7 == i || 8 == i || 10 == i || 12 == i){
			daysOfMonth = 31;
		}
		else{
			daysOfMonth = 30;
		}
		
		for (int j = 1; j <= daysOfMonth; j++, col++){
			//����
			if (20 == col){
				col = 0;
				row++;
			}
			//Ȧ������ �� �� 
			if (month > i || (month == i && nowDay >= j)){
				pDc->SetTextColor(RGB(0, 0, 0));
			}
			else{
				pDc->SetTextColor(RGB(125, 125, 125));
			}
			CString cstr;
			cstr.Format(TEXT("%d"), j);
			pDc->TextOut(calendarLeft + partWidth*col + 3, calendarTop + partHeight*row + 2, cstr);
			
		}
	}
	

}

void EventDlg::OnBnClickedYearCalendarButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	showEventButton(FALSE);
	CRect Rect;
	GetDlgItem(IDC_TEMP_STATIC)->GetClientRect(&Rect);
	ScreenToClient(Rect);
	CDC* pDc = this->GetDC();
	InvalidateRect(&Rect);//��cr_DrawRect�������ػ�
	GetDlgItem(IDC_TEMP_STATIC)->ShowWindow(FALSE);
	UpdateWindow();
	DrawYearCalendar(pDc, Rect);
	
}
void EventDlg::ReadEventFile(CString filePath){
	CFile file;
	if (file.Open(filePath, CFile::modeRead) == 0)
	{
		MessageBox(filePath + "��ȡ�ļ�ʧ��!", NULL, MB_ICONEXCLAMATION);
		return;
	}
	int size = file.GetLength();
	char* pText = new char[size + 1];
	int nRet = file.Read(pText, size);
	file.Close();
	pText[nRet] = 0;
	m_csEventContent = (CString)pText;
	UpdateData(FALSE);
}
void EventDlg::OnBnClickedTodayButton()
{
	m_csYear.Format("%d", m_iCurYear);
	m_csMonth.Format("%02d", m_iCurMonth);
	m_csDay.Format("%02d", m_iDayOfMonth);
	m_csEventFilePathToday = m_csEventfFolderPath + _T("\\") + m_csYear + m_csMonth + m_csDay + _T(".sch");
	m_cmMonthControl.SetCurSel(CTime(m_iCurYear, m_iCurMonth, m_iDayOfMonth, 0, 0, 0));

	m_csEventContent = "";
	UpdateData(FALSE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (PathFileExists(m_csEventFilePathToday)){
		ReadEventFile(m_csEventFilePathToday);
	}
	m_iSelect = TODAY;
	GetDlgItem(IDC_TODAY_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_TOMORROW_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_DAY_AFTER_TOM_BUTTON)->EnableWindow(TRUE);
}
void EventDlg::OnBnClickedTomorrowButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_csYear.Format("%d", m_iCurYear);
	int daysOfMonth = dayOfMonths[m_iCurMonth];
	if ((m_iCurYear % 4 == 0 && m_iCurYear % 100) || (m_iCurYear % 400 == 0)){
		daysOfMonth = 29;
	}
	m_csDay.Format("%02d", m_iDayOfMonth + 1);
	//��ĩ
	if (m_iDayOfMonth == daysOfMonth){
		if (m_iCurMonth == 12){
			m_csMonth.Format("%02d", 1);
		}
		else{
			m_csMonth.Format("%02d", m_iCurMonth + 1);
		}
		m_csDay.Format("%02d", 1);
	}
	m_csEventFilePathTomorrow = m_csEventfFolderPath + _T("\\") + m_csYear + m_csMonth + m_csDay + _T(".sch");
	m_cmMonthControl.SetCurSel(CTime(m_iCurYear, _ttoi(m_csMonth), _ttoi(m_csDay), 0, 0, 0));

	m_csEventContent = "";
	UpdateData(FALSE);
	if (PathFileExists(m_csEventFilePathTomorrow)){
		ReadEventFile(m_csEventFilePathTomorrow);
	}
	m_iSelect = TOMORROW;
	GetDlgItem(IDC_TODAY_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_TOMORROW_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_DAY_AFTER_TOM_BUTTON)->EnableWindow(TRUE);
}
void EventDlg::OnBnClickedDayAfterTomButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_csYear.Format("%d", m_iCurYear);
	int daysOfMonth = dayOfMonths[m_iCurMonth - 1];
	m_csDay.Format("%02d", m_iDayOfMonth + 2);
	//��ĩ
	if (daysOfMonth - m_iDayOfMonth <= 1){
		m_csMonth.Format("%02d", 1);
		if (daysOfMonth - m_iDayOfMonth == 1){
			m_csDay.Format("%02d", 1);
		}
		else{
			m_csDay.Format("%02d", 2);
		}
	}
	m_csEventFilePathDayAfter = m_csEventfFolderPath + _T("\\") + m_csYear + m_csMonth + m_csDay + _T(".sch");
	m_cmMonthControl.SetCurSel(CTime(m_iCurYear, _ttoi(m_csMonth), _ttoi(m_csDay), 0, 0, 0));

	m_csEventContent = "";
	UpdateData(FALSE);
	if (PathFileExists(m_csEventFilePathDayAfter)){
		ReadEventFile(m_csEventFilePathDayAfter);
	}
	m_iSelect = DAYAFTER;
	GetDlgItem(IDC_TODAY_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_TOMORROW_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_DAY_AFTER_TOM_BUTTON)->EnableWindow(FALSE);
}


void EventDlg::OnBnClickedSaveButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (_ttoi(m_csYear) != m_iCurYear){
		MessageBox(_T("ֻ�ɱ��汾����¼�"), NULL, MB_ICONEXCLAMATION);
		return;
	}
	UpdateData(TRUE);
	CreatMultiDir(m_csEventfFolderPath);
	CFile file;
	switch (m_iSelect)
	{
	case TODAY:
		if (m_csEventContent == "" && PathFileExists(m_csEventFilePathToday)){
			file.Remove(m_csEventFilePathToday);
		}
		else if (m_csEventContent != ""){
			if (file.Open(m_csEventFilePathToday, CFile::modeWrite | CFile::modeCreate) == 0)
			{
				MessageBox(m_csEventFilePathToday + _T("����ʧ��!"), NULL, MB_ICONEXCLAMATION);
				return;
			}
			file.Write(m_csEventContent, m_csEventContent.GetLength());
		}
		break;
	case TOMORROW:
		if (m_csEventContent == "" && PathFileExists(m_csEventFilePathTomorrow)){
			file.Remove(m_csEventFilePathTomorrow);
		}
		else if(m_csEventContent != ""){
			if (file.Open(m_csEventFilePathTomorrow, CFile::modeWrite | CFile::modeCreate) == 0)
			{
				MessageBox(m_csEventFilePathTomorrow + _T("����ʧ��!"), NULL, MB_ICONEXCLAMATION);
				return;
			}
			file.Write(m_csEventContent, m_csEventContent.GetLength());
		}
		break;
	case DAYAFTER:
		if (m_csEventContent == "" && PathFileExists(m_csEventFilePathDayAfter)){
			file.Remove(m_csEventFilePathDayAfter);
		}
		else if (m_csEventContent != ""){
			if (file.Open(m_csEventFilePathDayAfter, CFile::modeWrite | CFile::modeCreate) == 0)
			{
				MessageBox(m_csEventFilePathDayAfter + _T("����ʧ��!"), NULL, MB_ICONEXCLAMATION);
				return;
			}
			file.Write(m_csEventContent, m_csEventContent.GetLength());
		}
		break;
	case SELECT:
		if (m_csEventContent == "" && PathFileExists(m_csEventFilePathSelect)){
			file.Remove(m_csEventFilePathSelect);
		}
		else if (m_csEventContent != ""){
			if (file.Open(m_csEventFilePathSelect, CFile::modeWrite | CFile::modeCreate) == 0)
			{
				MessageBox(m_csEventFilePathSelect + _T("����ʧ��!"), NULL, MB_ICONEXCLAMATION);
				return;
			}
			file.Write(m_csEventContent, m_csEventContent.GetLength());
		}
	default:
		break;
	}
	file.Flush();
	file.Close();
	LoadEventFile(m_csEventfFolderPath);//���¶����¼���Ϣ
	ReFreshCalendar(_ttoi(m_csMonth) - 1);
}


void EventDlg::OnMcnSelchangeMonthcalendar(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMonthCalCtrl* mcc = (CMonthCalCtrl*)GetDlgItem(IDC_MONTHCALENDAR);
	CTime time;
	mcc->GetCurSel(time);
	m_csYear.Format("%d", time.GetYear());
	m_csMonth.Format("%02d", time.GetMonth());
	m_csDay.Format("%02d", time.GetDay());
	m_csEventFilePathSelect = m_csEventfFolderPath + _T("\\") + m_csYear + m_csMonth + m_csDay + _T(".sch");
	
	m_csEventContent = "";
	UpdateData(FALSE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (PathFileExists(m_csEventFilePathSelect)){
		ReadEventFile(m_csEventFilePathSelect);
	}
	m_iSelect = SELECT;
	GetDlgItem(IDC_TODAY_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_TOMORROW_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_DAY_AFTER_TOM_BUTTON)->EnableWindow(TRUE);


	//�¼��Ӵ� ֻ�Ӵֱ����
	if (time.GetYear() == m_iCurYear){
		ReFreshCalendar(time.GetMonth() - 1);
	}
	

	*pResult = 0;
}
void EventDlg::LoadEventFile(CString folderpath){
	m_ivecEvents.clear();
	m_ivecEvents.resize(12);
	CFileFind finder;
	BOOL exit = finder.FindFile(folderpath + _T("\\*.*"));
	while (exit){
		exit = finder.FindNextFile();
		if (!finder.IsDirectory() && !finder.IsDots()){
			CString mFile = finder.GetFileName();
			if (mFile.GetLength() == 12){//20190405.sch 12λ
				CString year = mFile.Left(4);
				CString month = mFile.Mid(4, 2);
				CString day = mFile.Mid(6, 2);
				if (_ttoi(year) != m_iCurYear){//ֻ���������¼�
					continue;
				}
				m_ivecEvents[_ttoi(month) - 1].push_back(_ttoi(day));
			}
		}
	}
	finder.Close();
}
void EventDlg::ReFreshCalendar(int findMonth){
	int nCount;
	SYSTEMTIME timeFrom;
	SYSTEMTIME timeUntil;
	nCount = m_cmMonthControl.GetMonthRange(&timeFrom, &timeUntil, GMR_DAYSTATE);//����������ʾ���·��������ؼ���No Trailing Dates������ΪTrue֮��һ��ҳ�������ʾһ���·�
	int nIndex = (timeFrom.wDay == 1) ? 0 : 1;
	//�Ӵ�
	LPMONTHDAYSTATE pDayState;//����״̬�ṹ��
	pDayState = new MONTHDAYSTATE[nCount];
	memset(pDayState, 0, sizeof(MONTHDAYSTATE)* nCount);
	for (int i = 0; i < m_ivecEvents[findMonth].size(); i++){
		pDayState[nIndex] |= 1 << (m_ivecEvents[findMonth][i] - 1);
	}
	VERIFY(m_cmMonthControl.SetDayState(nCount, pDayState));
	delete[]pDayState;
}
void EventDlg::showEventButton(bool isShow){
	m_cmMonthControl.ShowWindow(isShow);
	CEdit *edit = (CEdit*)GetDlgItem(IDC_EVENT_CONTENT_EDIT);
	edit->ShowWindow(isShow);
	CButton *button = (CButton*)GetDlgItem(IDC_TODAY_BUTTON);
	button->ShowWindow(isShow);
	button = (CButton*)GetDlgItem(IDC_TOMORROW_BUTTON);
	button->ShowWindow(isShow);
	button = (CButton*)GetDlgItem(IDC_DAY_AFTER_TOM_BUTTON);
	button->ShowWindow(isShow);
	button = (CButton*)GetDlgItem(IDC_SAVE_BUTTON);
	button->ShowWindow(isShow);
}