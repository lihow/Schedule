#pragma once
#include "afxwin.h"
#include "public.h"

// WantToBeDlg 对话框

class WantToBeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WantToBeDlg)

public:
	WantToBeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~WantToBeDlg();

//保存路径
	CString m_csWTBFolderPath = rootFolder + "wtb";
	CString m_csWTBFilePath;
	void readWTBFile(CString filePath);

// 对话框数据
	enum { IDD = IDD_WANT_TO_BE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSaveButton();
	CString m_csSaveStatus;
	CString m_csWTBContent;
	CString m_csNowContent;
	CFont font;
};
