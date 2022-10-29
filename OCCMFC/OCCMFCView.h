
// OCCMFCView.h: COCCMFCView 类的接口
//

#pragma once

class COCCMFCView : public CView
{
protected: // 仅从序列化创建
	COCCMFCView() noexcept;
	DECLARE_DYNCREATE(COCCMFCView)

// 特性
public:
	COCCMFCDoc* GetDocument() const;
	Handle(V3d_View) myView;
// 操作
public:
	virtual void OnInitialUpdate();
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	void DrawRectangle(Standard_Integer theMinX, Standard_Integer theMinY, Standard_Integer theMaxX, Standard_Integer theMaxY,
		Standard_Boolean theToDraw, Aspect_TypeOfLine theLineType = Aspect_TOL_SOLID);
// 实现
public:
	virtual ~COCCMFCView();
	void FitAll() { myView->FitAll();  myView->ZFitAll(); };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	Standard_Integer     myXmin;
	Standard_Integer     myYmin;
	Standard_Integer     myXmax;
	Standard_Integer     myYmax;
	Handle(AIS_RubberBand)    myRect;
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // OCCMFCView.cpp 中的调试版本
inline COCCMFCDoc* COCCMFCView::GetDocument() const
   {
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CViewer3dDoc)));
	return (COCCMFCDoc*)m_pDocument;
}
#endif

