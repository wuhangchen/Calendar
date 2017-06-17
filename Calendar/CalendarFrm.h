#if !defined(AFX_CALENDARFRM_H__9EC203BC_1574_4986_B73C_A44C975739CC__INCLUDED_)
#define AFX_CALENDARFRM_H__9EC203BC_1574_4986_B73C_A44C975739CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Calendar1.h"
// CalendarFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalendarFrm window
/////////////////////////////////////////////////////////////////////////////
// CYearEdit window

class CYearEdit : public CEdit
{
	// Construction
public:
	CYearEdit();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYearEdit)
public:
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID);
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CYearEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CYearEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CCalendarFrm : public CWnd
{
private:
	CCalendar        m_oCalendar;
	CSpinButtonCtrl  m_oYearSelect;
	CComboBox        m_oMonthSelect;
	CYearEdit        m_oYearEdit;
	CButton          m_obutToday;
	CFont            m_oDispFont;
	// Construction
public:
	CCalendarFrm();

	// Attributes
public:
	void SetDate(WORD iYear, WORD iMonth, WORD iDay)
	{
		m_oCalendar.SetDate(iYear, iMonth, iDay);
	}
	void GetDate(WORD &iYear, WORD &iMonth, WORD &iDay)
	{
		m_oCalendar.GetDate(iYear, iMonth, iDay);
	}

	CFont * GetDispFont() { return &m_oDispFont; }
	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarFrm)
public:
	virtual BOOL Create(RECT &rect, CWnd * pParentWnd, UINT nID);
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CCalendarFrm();

	// Generated message map functions
private:
	void l_PaintToday(CPaintDC &dc);
	void l_PaintBorder(CPaintDC &dc);
	void l_PaintChineseInfo(CPaintDC &dc);
	void l_CreateDispFont();

protected:
	//{{AFX_MSG(CCalendarFrm)
	afx_msg void OnPaint();
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg LRESULT OnSelChange(WPARAM iYearMonth, LPARAM iDay);
	afx_msg void OnMonthChange();
	afx_msg void OnYearChange();
	afx_msg void OnTodayClick();

	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARFRM_H__9EC203BC_1574_4986_B73C_A44C975739CC__INCLUDED_)
