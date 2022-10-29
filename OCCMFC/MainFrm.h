
// MainFrm.h: CMainFrame 类的接口
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
	void setProgressCtrl(int value);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	CProgressCtrl     m_wndProgress;
	HICON             m_hIcon;
	CBitmap           m_bitmap1;
	CBitmap           m_bitmap2;
	CBitmap           m_bitmapIfc;
	ITaskbarList3* m_pTaskbarList;
// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

};


