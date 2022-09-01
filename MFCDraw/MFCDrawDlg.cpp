
// MFCDrawDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCDraw.h"
#include "MFCDrawDlg.h"
#include "afxdialogex.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCDrawDlg 对话框



CMFCDrawDlg::CMFCDrawDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDRAW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CChartCtrl m_ChartCtrl;  //这里的成员变量名称根据实际需要命名即可

void CMFCDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM1, m_ChartCtrl);
}

BEGIN_MESSAGE_MAP(CMFCDrawDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCDrawDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCDrawDlg 消息处理程序

BOOL CMFCDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//初始化坐标轴
	CChartAxis* pAxis = NULL;
	pAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);	//底部坐标轴
	//pAxis->SetAutomatic(true);	
	//根据具体数值自动调节坐标轴坐标，如果要固定坐标轴需要将其参数修改为false
	pAxis->SetAutomatic(false);
	pAxis->SetMinMax(0, 100);	//固定x轴坐标为0-100
	pAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);	//左边坐标轴
	pAxis->SetAutomatic(false);
	pAxis->SetMinMax(0, 100);	//固定y轴坐标为0-10

	//添加标题
	TChartString str;
	str = _T("High-speed Charting画图Demo");
	m_ChartCtrl.GetTitle()->AddString(str);

	//设置颜色
	m_ChartCtrl.GetTitle()->SetColor(RGB(255, 255, 255));   //标题字体白色
	m_ChartCtrl.GetLeftAxis()->SetTextColor(RGB(255, 255, 255));  //左坐标轴白色
	m_ChartCtrl.GetBottomAxis()->SetTextColor(RGB(255, 255, 255));  //底部坐标轴白色
	m_ChartCtrl.SetBorderColor(RGB(255, 255, 255));  //边框颜色白色
	m_ChartCtrl.SetBackColor(RGB(85, 85, 85));  //背景颜色深灰色

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCDrawDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	double X1Values[10], Y1Values[10];

	std::vector<double> x = { 1.0, 2.0, 4.0, 6.0, 10.0, 40.0, 60.0, 100.0 };
	std::vector<double> y = { 34.0, 13.0, 56.0, 36.0, 18.0, 40.0, 60.0, 60.0 };

	for (int i = 0; i < x.size() ; i++)
	{
		X1Values[i] = x[i];
		Y1Values[i] = y[i];
	}

	CChartLineSerie *pLineSerie;
	CChartPointsSerie *pPointSerie;

	m_ChartCtrl.SetZoomEnabled(true);
	m_ChartCtrl.RemoveAllSeries();//先清空
	//pLineSerie = m_ChartCtrl.CreateLineSerie();
	//pLineSerie->SetSeriesOrdering(poNoOrdering);//设置为无序
	//pLineSerie->SetPoints(X1Values, Y1Values, 10);
	
	pPointSerie = m_ChartCtrl.CreatePointsSerie();
	pPointSerie->SetSeriesOrdering(poNoOrdering);//设置为无序
	pPointSerie->SetPoints(X1Values, Y1Values, 10);
	pPointSerie->SetBorderColor(RGB(255, 255, 255));
}

void CMFCDrawDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCDrawDlg::OnPaint()
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
HCURSOR CMFCDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




