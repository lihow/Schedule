
// Schedule.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CScheduleApp: 
// �йش����ʵ�֣������ Schedule.cpp
//

class CScheduleApp : public CWinApp
{
public:
	CScheduleApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CScheduleApp theApp;