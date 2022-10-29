
// OCCMFCView.cpp: COCCMFCView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OCCMFC.h"
#endif

#include "OCCMFCDoc.h"
#include "OCCMFCView.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif


// COCCMFCView

IMPLEMENT_DYNCREATE(COCCMFCView, CView)

BEGIN_MESSAGE_MAP(COCCMFCView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// COCCMFCView 构造/析构

COCCMFCView::COCCMFCView() noexcept
{
	// TODO: 在此处添加构造代码
	myRect = new AIS_RubberBand(Quantity_NOC_WHITE, Aspect_TOL_SOLID, 1.0);
}

COCCMFCView::~COCCMFCView()
{
}

BOOL COCCMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COCCMFCView 绘图

void COCCMFCView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	myView = GetDocument()->GetViewer()->CreateView();
	Handle(WNT_Window) aWntWindow = new WNT_Window(GetSafeHwnd());
	myView->SetWindow(aWntWindow);
	if (!aWntWindow->IsMapped()) {
		aWntWindow->Map();
	}

	GetDocument()->GetIC()->SetDisplayMode(AIS_Shaded, Standard_True);
	myView->SetComputedMode(Standard_False);
	myView->Redraw();
}

void COCCMFCView::OnDraw(CDC* /*pDC*/)
{
	COCCMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	myView->Redraw();
}


// COCCMFCView 打印

BOOL COCCMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COCCMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COCCMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void COCCMFCView::DrawRectangle(Standard_Integer theMinX, Standard_Integer theMinY, Standard_Integer theMaxX, Standard_Integer theMaxY, Standard_Boolean theToDraw, Aspect_TypeOfLine theLineType)
{
	const Handle(AIS_InteractiveContext)& aCtx = GetDocument()->GetIC();
	if (!theToDraw)
	{
		aCtx->Remove(myRect, false);
		aCtx->CurrentViewer()->RedrawImmediate();
		return;
	}

	CRect aRect;
	GetWindowRect(aRect);
	myRect->SetLineType(theLineType);
	myRect->SetRectangle(theMinX, aRect.Height() - theMinY, theMaxX, aRect.Height() - theMaxY);
	if (!aCtx->IsDisplayed(myRect))
	{
		aCtx->Display(myRect, false);
	}
	else
	{
		aCtx->Redisplay(myRect, false);
	}
	aCtx->CurrentViewer()->RedrawImmediate();
}


// COCCMFCView 诊断

#ifdef _DEBUG
void COCCMFCView::AssertValid() const
{
	CView::AssertValid();
}

void COCCMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COCCMFCDoc* COCCMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COCCMFCDoc)));
	return (COCCMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// COCCMFCView 消息处理程序


void COCCMFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnMouseMove(nFlags, point);
	//   ============================  LEFT BUTTON =======================
	if (nFlags & MK_LBUTTON)
	{
		if (nFlags & MK_CONTROL)
		{
			// move with MB1 and Control : on the dynamic zooming  
			// Do the zoom in function of mouse's coordinates  
			myView->Zoom(myXmax, myYmax, point.x, point.y);
			// save the current mouse coordinate in min 
			myXmax = point.x;
			myYmax = point.y;
		}
		else // if ( Ctrl )
		{
			myXmax = point.x;
			myYmax = point.y;
			if (nFlags & MK_SHIFT)
				GetDocument()->ShiftDragEvent(myXmax, myYmax, 0, myView);
			else
				GetDocument()->DragEvent(myXmax, myYmax, 0, myView);
			DrawRectangle(myXmin, myYmin, myXmax, myYmax, Standard_True);
		}
	}else
	//   ============================  MIDDLE BUTTON =======================
	if (nFlags & MK_MBUTTON)
	{
		myView->Pan(point.x - myXmax, myYmax - point.y); // Realize the panning
		myXmax = point.x; myYmax = point.y;
	}else
	//   ============================  RIGHT BUTTON =======================
	if (nFlags & MK_RBUTTON)
	{
		myView->Rotation(point.x, point.y);
	}else
		//   ============================  NO BUTTON =======================
	{  // No buttons 
		myXmax = point.x; myYmax = point.y;
		GetDocument()->MoveEvent(point.x, point.y, myView);
	}
}


void COCCMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nFlags & MK_CONTROL)
	{
		return;
	}
	myXmin = point.x;  myYmin = point.y;
	myXmax = point.x;  myYmax = point.y;
	if (nFlags & MK_SHIFT)
		GetDocument()->ShiftDragEvent(myXmax, myYmax, -1, myView);
	else
		GetDocument()->DragEvent(myXmax, myYmax, -1, myView);
	CView::OnLButtonDown(nFlags, point);
}


void COCCMFCView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nFlags & MK_CONTROL)
	{
		return;
	}
	if (point.x == myXmin && point.y == myYmin)
	{
		myXmax = point.x;
		myYmax = point.y;
		if (nFlags & MK_SHIFT)
			GetDocument()->ShiftInputEvent(point.x, point.y, myView);
		else
			GetDocument()->InputEvent(point.x, point.y, myView);
	}
	else
	{
		DrawRectangle(myXmin, myYmin, myXmax, myYmax, Standard_False);
		myXmax = point.x;
		myYmax = point.y;
		if (nFlags & MK_SHIFT)
			GetDocument()->ShiftDragEvent(point.x, point.y, 1, myView);
		else
			GetDocument()->DragEvent(point.x, point.y, 1, myView);
	}
	CView::OnLButtonUp(nFlags, point);
}


BOOL COCCMFCView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Standard_Integer aFactor = 16;

	Standard_Integer aX = pt.x;
	Standard_Integer aY = pt.y;

	if (zDelta > 0)
	{
		aX += aFactor;
		aY += aFactor;
	}
	else
	{
		aX -= aFactor;
		aY -= aFactor;
	}

	myView->Zoom(pt.x, pt.y, aX, aY);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void COCCMFCView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	myView->StartRotation(point.x, point.y);
	CView::OnRButtonDown(nFlags, point);
}


void COCCMFCView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	CView::OnRButtonUp(nFlags, point);
}


void COCCMFCView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (!myView.IsNull())
		myView->MustBeResized();
}
