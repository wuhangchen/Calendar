// CalendarFrm.cpp : implementation file
//

#include "stdafx.h"
#include "Calendar.h"
#include "CalendarFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendarFrm

CCalendarFrm::CCalendarFrm()
{
}

CCalendarFrm::~CCalendarFrm()
{
}


BEGIN_MESSAGE_MAP(CCalendarFrm, CWnd)
	//{{AFX_MSG_MAP(CCalendarFrm)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_SELCHANGE, OnSelChange)
	ON_CBN_SELCHANGE(IDC_MONTHSELECT, OnMonthChange)
	ON_EN_CHANGE(IDC_YEAREDIT, OnYearChange)
	ON_BN_CLICKED(IDC_BUTTODAY, OnTodayClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarFrm message handlers

BOOL CCalendarFrm::Create(RECT &rect, CWnd * pParentWnd, UINT nID)
{
	CString szClassName = AfxRegisterWndClass(CS_CLASSDC | CS_SAVEBITS |
		CS_HREDRAW | CS_VREDRAW,
		0, 0, 0);

	rect.right = rect.left + 340;
	rect.bottom = rect.top + 214;
	//WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE
	//|WS_DLGFRAME|WS_THICKFRAME
	if (!CWnd::CreateEx(0, szClassName, _T(""),
		WS_DLGFRAME | WS_CHILD | WS_VISIBLE | WS_TABSTOP, rect,
		pParentWnd, nID, NULL))

		return FALSE;

	UpdateWindow();
	l_CreateDispFont();
	return TRUE;
}

void CCalendarFrm::l_PaintToday(CPaintDC &dc)
{
#define STARTX  102
#define STARTY  155
	SYSTEMTIME systime;
	::GetSystemTime(&systime);
	CString str;
	str.Format("今天：%4d年%2d月%2d日", systime.wYear, systime.wMonth, systime.wDay);
	dc.Draw3dRect(STARTX, STARTY, 227, 22, RGB(128, 128, 128), RGB(255, 255, 255));
	dc.SetBkColor(::GetSysColor(4));
	dc.TextOut(STARTX + 4, STARTY + 4, str);
#undef  STARTY
#undef  STARTX
}

void CCalendarFrm::l_PaintBorder(CPaintDC &dc)
{
	CRect rect;
	GetClientRect(&rect);
	/*rect.left ++;
	rect.top ++;
	dc.FrameRect(&rect, &CBrush(RGB(255,255,255)));
	rect -= CPoint(1,1);
	dc.FrameRect(&rect, &CBrush(RGB(128,128,128)));
	*/
#define LINEY  179
	rect.SetRect(rect.left + 1, LINEY, rect.right + 1, LINEY + 2);
	dc.Draw3dRect(&rect, RGB(128, 128, 128), RGB(255, 255, 255));

#define LINEX  96
	rect.SetRect(LINEX, 1, LINEX + 2, LINEY + 2);
	dc.Draw3dRect(&rect, RGB(128, 128, 128), RGB(255, 255, 255));
#undef  LINEX
#undef  LINEY

}
void CCalendarFrm::l_PaintChineseInfo(CPaintDC &dc)
{
	WORD iYear, iMonth, iDay;
#define DISP_X  15
#define DISP_Y  55
	WORD iHolDay = CCalendar::GetLunarDate(m_oCalendar.GetYear(),
		m_oCalendar.GetMonth(),
		m_oCalendar.GetDay(),
		iYear, iMonth, iDay);
	char text[18];
	CCalendar::FormatLunarYear(iYear, text);
	dc.SetBkColor(::GetSysColor(4));
	dc.TextOut(DISP_X, DISP_Y, text);
	CCalendar::FormatMonth(iMonth, text);
	dc.TextOut(DISP_X + 23, DISP_Y + 20, text);
	CCalendar::FormatLunarDay(iDay, text);
	dc.TextOut(DISP_X + 39, DISP_Y + 40, text);
	char *HolText[] = { "小寒", "大寒", "立春", "雨水",
									"惊蛰", "春分", "清明", "谷雨",
									"立夏", "小满", "芒种", "夏至",
									"小暑", "大暑", "立秋", "处暑",
									"白露", "秋分", "寒露", "霜降",
									"立冬", "小雪", "大雪", "冬至" };


	if (iHolDay)
	{
		strcpy(text, "今日 ");
		strcat(text, HolText[iHolDay - 1]);
		dc.TextOut(DISP_X, DISP_Y + 80, text);
	}
	else
		dc.TextOut(DISP_X, DISP_Y + 80, "         ");
#undef DISP_X
#undef DISP_Y
}

void CCalendarFrm::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.SelectObject(GetDispFont());
	l_PaintBorder(dc);
	l_PaintChineseInfo(dc);
	l_PaintToday(dc);

}

int CCalendarFrm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//create calendar
	CRect rect;
	GetClientRect(&rect);
	rect.left = rect.CenterPoint().x - 64;
	rect.top += 2;
	if (!m_oCalendar.Create(rect, this, IDC_CALENDAR))
		return -1;

#define LEFT_X   2
#define TOP_Y    2
#define WIDTH    90
#define HEIGHT   22
	//create select year spingbutton and buddy
	rect.SetRect(LEFT_X, TOP_Y, LEFT_X + WIDTH, TOP_Y + HEIGHT);
	if (!m_oYearEdit.Create(rect, this, IDC_YEAREDIT))
		return -1;
	m_oYearEdit.SetLimitText(4);

	rect.SetRect(79, 3, 98, 23);
	if (!m_oYearSelect.Create(UDS_NOTHOUSANDS | WS_CHILD | WS_TABSTOP |
		WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
		rect, this, IDC_YEARSELECT))
		return -1;
	m_oYearSelect.SetBuddy(&m_oYearEdit);
	m_oYearSelect.SetRange(START_YEAR, END_YEAR);
	m_oYearSelect.SetPos(m_oCalendar.GetYear());

	//create select month combobox	
	rect.SetRect(LEFT_X, TOP_Y + HEIGHT + 2, LEFT_X + WIDTH, TOP_Y + 8 * HEIGHT + 2);
	if (!m_oMonthSelect.Create(WS_VSCROLL | CBS_DROPDOWNLIST | WS_CHILD |
		WS_VISIBLE | WS_TABSTOP,
		rect, this, IDC_MONTHSELECT))
		return -1;
#undef LEFT_X
#undef TOP_Y	
#undef WIDTH 
#undef HEIGHT
	//create today button
	rect.SetRect(255, 184, 328, 206);
	if (!m_obutToday.Create("今天", WS_CHILD | WS_VISIBLE | WS_TABSTOP, rect, this, IDC_BUTTODAY))
		return -1;

	char text[10];
	for (int i = 0; i<12; i++)
	{
		CCalendar::FormatMonth(i + 1, text, FALSE);
		m_oMonthSelect.AddString(text);
	}
	m_oMonthSelect.SetCurSel(m_oCalendar.GetMonth() - 1);

	return 0;

}

LRESULT CCalendarFrm::OnSelChange(WPARAM iYearMonth, LPARAM iDay)
{
	Invalidate(FALSE);
	return 0;
}

void CCalendarFrm::OnMonthChange()
{
	WORD iYear, iDay, iMonth;
	m_oCalendar.GetDate(iYear, iMonth, iDay);
	iMonth = m_oMonthSelect.GetCurSel() + 1;

	if (iMonth != m_oCalendar.GetMonth())
	{
		if (iDay > CCalendar::MonthDays(iYear, iMonth))
			iDay = CCalendar::MonthDays(iYear, iMonth);
		m_oCalendar.SetDate(iYear, iMonth, iDay);
		Invalidate();
	}

}
void CCalendarFrm::OnYearChange()
{

	CString text;
	m_oYearEdit.GetWindowText(text);
	if (text.GetLength()<4)
		return;

	WORD iYear, iMonth, iDay;
	m_oCalendar.GetDate(iYear, iMonth, iDay);
	iYear = m_oYearSelect.GetPos();

	if (iYear != m_oCalendar.GetYear())
	{
		if (iDay > CCalendar::MonthDays(iYear, iMonth))
			iDay = CCalendar::MonthDays(iYear, iMonth);
		m_oCalendar.SetDate(iYear, iMonth, iDay);
		text.Format("%4d", iYear);
		m_oYearEdit.SetWindowText(text);
		Invalidate();
	}

}

void CCalendarFrm::OnTodayClick()
{
	WORD iYear, iMonth, iDay;
	SYSTEMTIME systime;
	::GetSystemTime(&systime);

	iYear = systime.wYear;
	iMonth = systime.wMonth;
	iDay = systime.wDay;
	if (iYear != m_oCalendar.GetYear() || iMonth != m_oCalendar.GetMonth()
		|| iDay != m_oCalendar.GetDay())
	{
		SetDate(iYear, iMonth, iDay);
		m_oYearSelect.SetPos(iYear);
		m_oMonthSelect.SetCurSel(iMonth - 1);
		Invalidate();
	}
}
void CCalendarFrm::l_CreateDispFont()
{
	static LOGFONT logFont;
	memset(&logFont, 0, sizeof(logFont));

	logFont.lfHeight = 16;
	logFont.lfWeight = FW_NORMAL;
	logFont.lfWidth = 0;
	logFont.lfCharSet = GB2312_CHARSET;
	logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logFont.lfQuality = PROOF_QUALITY;
	logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	strcpy(logFont.lfFaceName, "Disp Font");

	m_oDispFont.CreateFontIndirect(&logFont);
	SetFont(&m_oDispFont, FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CYearEdit
CYearEdit::CYearEdit()
{
}

CYearEdit::~CYearEdit()
{
}


BEGIN_MESSAGE_MAP(CYearEdit, CEdit)
	//{{AFX_MSG_MAP(CYearEdit)
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYearEdit message handlers

BOOL CYearEdit::Create(const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::CreateEx(WS_EX_CLIENTEDGE, _T("EDIT"), NULL,
		WS_CHILD | WS_VISIBLE, rect, pParentWnd, nID);
}

void CYearEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar < '0' || nChar > '9')
		return;
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CYearEdit::OnKillFocus(CWnd* pNewWnd)
{
	char syear[6];
	GetWindowText(syear, 5);
	long iyear = atol(syear);

	if (iyear < START_YEAR)
	{
		sprintf(syear, "%4d", START_YEAR);
		SetWindowText(syear);
	}
	else if (iyear > END_YEAR)
	{
		sprintf(syear, "%4d", END_YEAR);
		SetWindowText(syear);
	}
	CEdit::OnKillFocus(pNewWnd);
}
