// CalendarDlg.h : header file
//

#if !defined(AFX_CALENDARDLG_H__BF68F177_5E57_4375_913F_D6059C675DAA__INCLUDED_)
#define AFX_CALENDARDLG_H__BF68F177_5E57_4375_913F_D6059C675DAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Calendarfrm.h"
/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg dialog

class CCalendarDlg : public CDialog
{
	// Construction
public:
	CCalendarDlg(CWnd* pParent = NULL);	// standard constructor

										// Dialog Data
										//{{AFX_DATA(CCalendarDlg)
	enum { IDD = IDD_CALENDAR_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
														//}}AFX_VIRTUAL

														// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCalendarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CCalendarFrm m_oCalendar;

public:
	afx_msg void OnBnClickedCancel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARDLG_H__BF68F177_5E57_4375_913F_D6059C675DAA__INCLUDED_)
