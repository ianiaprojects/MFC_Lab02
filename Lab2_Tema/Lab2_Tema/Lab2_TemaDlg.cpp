
// Lab2_TemaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Lab2_Tema.h"
#include "Lab2_TemaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLab2TemaDlg dialog



CLab2TemaDlg::CLab2TemaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LAB2_TEMA_DIALOG, pParent)
	, numarator(0)
	, numitor(0)
	, cmMdc(0)
	, cmmmc(0)
	, numarator_simplificat(0)
	, numitor_simplificat(0)
	, current_element(0)
	, current_list(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLab2TemaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUMARATOR, numarator);
	DDX_Text(pDX, IDC_NUMITOR, numitor);
	DDX_Text(pDX, IDC_CMMDC, cmMdc);
	DDX_Text(pDX, IDC_CMMMC, cmmmc);
	DDX_Text(pDX, IDC_SIMPLIFICARE_NUMARATOR, numarator_simplificat);
	DDX_Text(pDX, IDC_SIMPLIFICARE_NUMITOR, numitor_simplificat);
	DDX_Text(pDX, IDC_ELEMENT_CURENT, current_element);
	DDX_Text(pDX, IDC_CURRENT_LIST, current_list);
}

BEGIN_MESSAGE_MAP(CLab2TemaDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CALCULEAZA, &CLab2TemaDlg::OnBnClickedCalculeaza)
	ON_BN_CLICKED(IDC_ADAUGA, &CLab2TemaDlg::OnBnClickedAdauga)
	ON_BN_CLICKED(IDC_STERGE, &CLab2TemaDlg::OnBnClickedSterge)
END_MESSAGE_MAP()


// CLab2TemaDlg message handlers

BOOL CLab2TemaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLab2TemaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLab2TemaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLab2TemaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLab2TemaDlg::OnBnClickedCalculeaza()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	// First problem
	int cmMdc_result = number_list.GetAt(0);
	int cmmmc_result = number_list.GetAt(0);

	for (int i = 1; i < number_list.GetSize(); i++)
	{
		cmMdc_result = cmmdcResult(number_list.GetAt(i), cmMdc_result);
		cmmmc_result = (cmmmc_result * number_list.GetAt(i)) / (cmmdcResult(number_list.GetAt(i), cmMdc_result));
	}

	cmMdc = cmMdc_result;
	cmmmc = cmmmc_result;
	// Second problem

	if (numitor == 0)
	{
		AfxMessageBox((LPCWSTR)L"Numitorul nu poate fi niciodată nul!");
		return;
	}

	numarator_simplificat = numarator / cmmdcResult(numarator, numitor);
	numitor_simplificat = numitor / cmmdcResult(numarator, numitor);

	UpdateData(FALSE);
}

int CLab2TemaDlg::cmmdcResult(int x, int y)
{
	int r;
	if (y != 0)
		do
		{
			r = x % y;
			x = y;
			y = r;
		} while (r != 0);
	
		return x;
}

int CLab2TemaDlg::cmmmcResult(int x, int y)
{
	int r;

	r = x * y / cmmdcResult(x, y);

	return r;
}


void CLab2TemaDlg::OnBnClickedAdauga()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CString str;
	str.Format(_T(" %d"), current_element);

	current_list.Append(str);

	number_list.Add(current_element);
	current_element = 0;

	UpdateData(FALSE);
}


void CLab2TemaDlg::OnBnClickedSterge()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	current_element = 0;
	numarator = 0;
	numitor = 0;
	cmMdc = 0;
	cmmmc = 0;
	numarator_simplificat = 0;
	numitor_simplificat = 0;
	current_list = _T("");
	number_list.RemoveAll();

	UpdateData(FALSE);
}
