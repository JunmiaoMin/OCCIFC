
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "OCCMFC.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	IDS_STRING101,
	IDS_PROGRESS
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	HRESULT hr = CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, __uuidof(ITaskbarList3), (void**)&m_pTaskbarList);
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::setProgressCtrl(int value)
{
	m_wndProgress.SetPos(value);
	m_pTaskbarList->SetProgressValue(AfxGetMainWnd()->m_hWnd, value, 100);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("未能创建工具栏\n");
	//	return -1;      // 未能创建
	//}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	CRect rect;
	GetClientRect(rect);

	int width = rect.Width() / (2 * sizeof(indicators) / sizeof(UINT));

	for (int i = 0; i < sizeof(indicators) / sizeof(UINT) - 2; i++)
	{
		m_wndStatusBar.SetPaneInfo(i, indicators[i], SBPS_NORMAL, width);
	}
	m_wndStatusBar.SetPaneInfo(sizeof(indicators) / sizeof(UINT) - 2, indicators[sizeof(indicators) / sizeof(UINT) - 1],
		SBPS_STRETCH, 0);
	m_wndStatusBar.SetPaneInfo(sizeof(indicators) / sizeof(UINT) - 1, indicators[sizeof(indicators) / sizeof(UINT) - 1],
		SBPS_NORMAL, width);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	m_wndStatusBar.GetItemRect(sizeof(indicators) / sizeof(UINT) - 1, &rect);
	if (m_wndProgress.m_hWnd)
	{
		m_wndProgress.MoveWindow(rect);//移动进度条
	}
	else
	{
		m_wndProgress.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTH, rect, &m_wndStatusBar, 123);//创建进度条,位置就是状态栏的第二格子,父窗口为状态栏
		m_wndProgress.SetRange(0, 100);
		m_wndProgress.SetPos(0);
	}
	// TODO: 如果不需要可停靠工具栏，则删除这三行
	/*m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);*/
	m_bitmap1.LoadBitmap(IDB_BITMAP1);
	GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(1, MF_BYPOSITION, &m_bitmap1, &m_bitmap1);
	m_bitmap2.LoadBitmap(IDB_BITMAP2);
	GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(0, MF_BYPOSITION, &m_bitmap2, &m_bitmap2);
	m_bitmapIfc.LoadBitmap(IDB_BITMAP3);
	GetMenu()->GetSubMenu(1)->SetMenuItemBitmaps(ID_APP_ABOUT, MF_BYCOMMAND, &m_bitmapIfc, &m_bitmapIfc);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

