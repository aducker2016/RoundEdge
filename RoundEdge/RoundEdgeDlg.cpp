
// RoundEdgeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RoundEdge.h"
#include "RoundEdgeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CRoundEdgeDlg 对话框



CRoundEdgeDlg::CRoundEdgeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRoundEdgeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRoundEdgeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRoundEdgeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, &CRoundEdgeDlg::OnBnClickedButtonGenerate)
END_MESSAGE_MAP()


// CRoundEdgeDlg 消息处理程序

BOOL CRoundEdgeDlg::OnInitDialog()
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
	CRect rcW;
	GetWindowRect(&rcW);
	CRect rcC;
	GetClientRect(&rcC);
	MoveWindow(0, 0, 800 + rcW.Width() - rcC.Width(), 800 + 30 + rcW.Height() - rcC.Height());

	ModifyStyle(0, WS_CLIPCHILDREN);

	m_draw.Create(IDD_DIALOG_DRAW);
	m_draw.MoveWindow(0, 30, 800, 800);

	GetDlgItem(IDC_STATIC_1)->MoveWindow(415, 6, 30, 22);
	GetDlgItem(IDC_EDIT_RANGE)->MoveWindow(445, 4, 50, 22);
	GetDlgItem(IDC_STATIC_2)->MoveWindow(510, 6, 30, 22);
	GetDlgItem(IDC_EDIT_COUNT)->MoveWindow(540, 4, 50, 22);
	GetDlgItem(IDC_BUTTON_GENERATE)->MoveWindow(600, 2, 198, 26);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRoundEdgeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRoundEdgeDlg::OnPaint()
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
HCURSOR CRoundEdgeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRoundEdgeDlg::OnBnClickedButtonGenerate()
{
	// TODO:  在此添加控件通知处理程序代码
	int MAX_X = 80, MAX_Y = 80;
	std::vector<std::vector<int> >& nodes = m_draw.m_nodes;
	nodes.resize(MAX_X);
	for (int x = 0; x < MAX_X; x++)
	{
		nodes[x].resize(MAX_Y);
	}

	//已知点
	CString str;
	GetDlgItem(IDC_EDIT_RANGE)->GetWindowText(str);
	double range = _ttoi(str.GetBuffer());
	GetDlgItem(IDC_EDIT_COUNT)->GetWindowText(str);
	double count = _ttoi(str.GetBuffer());

	if (range <= 0 || count <= 0)
	{
		return;
	}

	double PI = 3.14159265358979323846;

	//背景
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			nodes[x][y] = 0;
		}
	}

	//计算圆边缘的点
	for (int i = 0; i < count; i++)
	{
		int angleX = 360 * i / count;
		int angleY = (angleX + 270) % 360;
		int x = MAX_X / 2 + (int)(cos(angleX * PI / 180) * range);
		int y = MAX_Y / 2 - (int)(cos(angleY * PI / 180) * range);
		if (x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y)
		{
			nodes[x][y] = 1;
		}
	}

	//中心点
	nodes[MAX_X / 2][MAX_Y / 2] = 2;

	m_draw.Invalidate();
}
