
// OCCMFCDoc.cpp: COCCMFCDoc 类的实现
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
#include "MainFrm.h"

#include <propkey.h>
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

// COCCMFCDoc

IMPLEMENT_DYNCREATE(COCCMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(COCCMFCDoc, CDocument)
	ON_COMMAND(ID_32771, &COCCMFCDoc::OnOpenIfc)
	ON_COMMAND(ID_32773, &COCCMFCDoc::OnNewFile)
END_MESSAGE_MAP()


// COCCMFCDoc 构造/析构

COCCMFCDoc::COCCMFCDoc() noexcept
{
	// TODO: 在此添加一次性构造代码
	AfxInitRichEdit();
	Handle(Graphic3d_GraphicDriver) theGraphicDriver = ((COCCMFCApp*)AfxGetApp())->GetGraphicDriver();

	myViewer = new V3d_Viewer(theGraphicDriver);
	myViewer->SetDefaultLights();
	myViewer->SetLightOn();

	myAISContext = new AIS_InteractiveContext(myViewer);
}

COCCMFCDoc::~COCCMFCDoc()
{
}

void COCCMFCDoc::ShiftDragEvent(const Standard_Integer theMouseX, const Standard_Integer theMouseY, const Standard_Integer theState, const Handle(V3d_View)& theView)
{
	// TheState == -1  button down
  // TheState ==  0  move
  // TheState ==  1  button up

	static Standard_Integer aStartDragX = 0;
	static Standard_Integer aStartDragY = 0;

	if (theState == -1)
	{
		// button down
		aStartDragX = theMouseX;
		aStartDragY = theMouseY;
	}

	if (theState == 0)
	{
		// button up
		myAISContext->ShiftSelect(aStartDragX, aStartDragY,
			theMouseX, theMouseY,
			theView, Standard_True);
	}
}

void COCCMFCDoc::DragEvent(const Standard_Integer theMouseX, const Standard_Integer theMouseY, const Standard_Integer theState, const Handle(V3d_View)& theView)
{
	// TheState == -1  button down
  // TheState ==  0  move
  // TheState ==  1  button up

	static Standard_Integer aStartDragX = 0;
	static Standard_Integer aStartDragY = 0;

	switch (theState)
	{
	case -1:
	{
		aStartDragX = theMouseX;
		aStartDragY = theMouseY;
		break;
	}
	case 0:
	{
		myAISContext->UpdateCurrentViewer();
		break;
	}
	case 1:
	{
		myAISContext->Select(aStartDragX, aStartDragY,
			theMouseX, theMouseY,
			theView, Standard_True);
		break;
	}
	};
}

void COCCMFCDoc::MoveEvent(const Standard_Integer theMouseX, const Standard_Integer theMouseY, const Handle(V3d_View)& theView)
{
	myAISContext->MoveTo(theMouseX, theMouseY, theView, Standard_True);
}

void COCCMFCDoc::ShiftInputEvent(const Standard_Integer, const Standard_Integer, const Handle(V3d_View)&)
{
	myAISContext->ShiftSelect(Standard_True);
}

void COCCMFCDoc::InputEvent(const Standard_Integer theMouseX, const Standard_Integer theMouseY, const Handle(V3d_View)& theView)
{
	myAISContext->MoveTo(theMouseX, theMouseY, theView, Standard_False);
	myAISContext->Select(Standard_True);
}

void COCCMFCDoc::Fit()
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
	COCCMFCView* pView = (COCCMFCView*)pChild->GetActiveView();
	pView->FitAll();
}

// COCCMFCDoc 序列化

void COCCMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void COCCMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void COCCMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void COCCMFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// COCCMFCDoc 诊断

#ifdef _DEBUG
void COCCMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COCCMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COCCMFCDoc 命令

void COCCMFCDoc::OnOpenIfc()
{
	// 构造打开文件对话框   
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CFileDialog fileDlg(TRUE, _T("ifc"), NULL, 0, _T("工业基础类(*.ifc)|*.ifc||"), pMain);
	if (IDOK == fileDlg.DoModal())
	{
		wstring strPathName = fileDlg.GetPathName().GetString();
		IfcParse::IfcFile file(IfcUtil::path::to_utf8(strPathName));
		if (file.good())
		{
			IfcGeom::IteratorSettings settings;
			std::vector<IfcGeom::filter_t> filter_funcs;
			IfcGeom::entity_filter entity_filter;
			entity_filter.entity_names.insert("IfcSpace");
			entity_filter.entity_names.insert("IfcOpeningElement");
			filter_funcs.push_back(boost::ref(entity_filter));
			settings.set(IfcGeom::IteratorSettings::Setting::USE_WORLD_COORDS, true);
			settings.set(IfcGeom::IteratorSettings::Setting::DISABLE_TRIANGULATION, true);
			int num_threads = std::max(std::thread::hardware_concurrency(), (unsigned int)1);
			IfcGeom::Iterator context_iterator(settings, &file, filter_funcs, num_threads);
			if (context_iterator.initialize())
			{
				do
				{
					pMain->setProgressCtrl(context_iterator.progress());
					IfcGeom::Element* geom_object = context_iterator.get();
					if (geom_object->product() && geom_object->product()->as<IfcSchema::IfcProduct>())
					{
						IfcSchema::IfcProduct* product = geom_object->product()->as<IfcSchema::IfcProduct>();
						IfcSchema::IfcProductRepresentation* productRepresentation = product->Representation();
						if (productRepresentation != nullptr)
						{
							aggregate_of<IfcSchema::IfcRepresentation>::ptr representations = productRepresentation->Representations();
							for (aggregate_of<IfcSchema::IfcRepresentation>::it it = representations->begin(); it != representations->end(); ++it)
							{
								IfcSchema::IfcRepresentation* representation = *it;
								IfcSchema::IfcSurfaceStyleRendering* surfaceStyleRendering = nullptr;
								aggregate_of<IfcSchema::IfcRepresentationItem >::ptr items = representation->Items();
								for (aggregate_of<IfcSchema::IfcRepresentationItem>::it it = items->begin(); it != items->end(); ++it)
								{
									IfcSchema::IfcRepresentationItem* representationItem = *it;
									aggregate_of<IfcSchema::IfcStyledItem >::ptr styledByItem = representationItem->StyledByItem();
									for (aggregate_of<IfcSchema::IfcStyledItem>::it it = styledByItem->begin(); it != styledByItem->end(); ++it)
									{
										IfcSchema::IfcStyledItem* styledItem = *it;
										aggregate_of<IfcSchema::IfcPresentationStyleAssignment >::ptr styles = styledItem->Styles();
										for (aggregate_of<IfcSchema::IfcPresentationStyleAssignment>::it it = styles->begin(); it != styles->end(); ++it)
										{
											IfcSchema::IfcPresentationStyleAssignment* presentationStyleAssignment = *it;
											aggregate_of_instance::ptr styles = presentationStyleAssignment->Styles();
											for (aggregate_of_instance::it it = styles->begin(); it != styles->end(); ++it)
											{
												IfcUtil::IfcBaseClass* baseClass = *it;
												IfcSchema::IfcSurfaceStyle* surfaceStyle = baseClass->as<IfcSchema::IfcSurfaceStyle>();
												if (surfaceStyle != nullptr)
												{
													aggregate_of_instance::ptr styles = surfaceStyle->Styles();
													for (aggregate_of_instance::it it = styles->begin(); it != styles->end(); ++it)
													{
														IfcUtil::IfcBaseClass* baseClass = *it;
														surfaceStyleRendering = baseClass->as<IfcSchema::IfcSurfaceStyleRendering>();
													}
												}
											}
										}
									}
								}
								const IfcGeom::BRepElement* brep = static_cast<const IfcGeom::BRepElement*>(geom_object);
								if (brep != nullptr)
								{
									TopoDS_Compound compound(brep->geometry_pointer()->as_compound());
									Handle(AIS_Shape) myAISSphere = new AIS_Shape(compound);
									if (surfaceStyleRendering != nullptr)
									{
										Quantity_Color color(surfaceStyleRendering->SurfaceColour()->Red(), surfaceStyleRendering->SurfaceColour()->Green()
											, surfaceStyleRendering->SurfaceColour()->Blue(), Quantity_TOC_RGB);
										myAISSphere->SetColor(color);
										myAISSphere->SetTransparency(surfaceStyleRendering->Transparency().get());
									};
									myAISContext->Display(myAISSphere, Standard_False);
								}
							}
						}
					}
				} while (context_iterator.next());
			}
			Fit();
			CString title = fileDlg.GetFileTitle();
			title.Format(_T("%s - OCCMFC"), title);
			pMain->SetWindowText(title);
			pMain->setProgressCtrl(0);
		}
	}
}


void COCCMFCDoc::OnNewFile()
{
	// TODO: 在此添加命令处理程序代码
	myAISContext->EraseAll(Standard_True);
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->SetWindowText(_T("无标题 - OCCMFC"));
}
