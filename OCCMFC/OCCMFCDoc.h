
// OCCMFCDoc.h: COCCMFCDoc 类的接口
//


#pragma once


class COCCMFCDoc : public CDocument
{
protected: // 仅从序列化创建
	COCCMFCDoc() noexcept;
	DECLARE_DYNCREATE(COCCMFCDoc)

// 特性
public:

// 操作
private:
	Handle(AIS_InteractiveContext) myAISContext;
	Handle(V3d_Viewer) myViewer;
public:
	Handle(V3d_Viewer) GetViewer(void) { return myViewer; }
	Handle(AIS_InteractiveContext) GetIC(void) { return myAISContext; }
	void ShiftDragEvent(const Standard_Integer theMouseX,
		const Standard_Integer theMouseY,
		const Standard_Integer theState,
		const Handle(V3d_View)& theView);
	void DragEvent(const Standard_Integer theMouseX,
		const Standard_Integer theMouseY,
		const Standard_Integer theState,
		const Handle(V3d_View)& theView);
	void MoveEvent(const Standard_Integer theMouseX,
		const Standard_Integer theMouseY,
		const Handle(V3d_View)& theView);
	void ShiftInputEvent(const Standard_Integer /*theMouseX*/,
		const Standard_Integer /*theMouseY*/,
		const Handle(V3d_View)& /*theView*/);
	void InputEvent(const Standard_Integer theMouseX,
		const Standard_Integer theMouseY,
		const Handle(V3d_View)& theView);
	static void Fit();
// 重写
public:
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~COCCMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnOpenIfc();
	afx_msg void OnNewFile();
};
