﻿// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
#include <Aspect_ScrollDelta.hxx>
#include <AIS_RubberBand.hxx>
#include <AIS_ViewController.hxx>
#include <BRepTools.hxx>  
#include <Standard_DefineHandle.hxx>  
#include <DsgPrs_LengthPresentation.hxx>  
#include <GCPnts_TangentialDeflection.hxx>  
#include <Geom_Axis2Placement.hxx>  
#include <Geom_CartesianPoint.hxx>  
#include <Geom_Line.hxx>  
#include <Geom_Surface.hxx>  
#include <BRepAdaptor_Surface.hxx>  
#include <GeomAbs_CurveType.hxx>  
#include <GeomAdaptor_Curve.hxx>  
#include <GeomTools_Curve2dSet.hxx>  
#include <gp_Vec.hxx>  
#include <Graphic3d_NameOfMaterial.hxx>  
#include <OSD_Environment.hxx>  
#include <Precision.hxx>  
#include <Prs3d_IsoAspect.hxx>  
#include <Prs3d_LineAspect.hxx>   
#include <Prs3d_Text.hxx>     
#include <Quantity_NameOfColor.hxx>  
#include <Quantity_PhysicalQuantity.hxx>  
#include <Quantity_TypeOfColor.hxx>  
#include <SelectMgr_EntityOwner.hxx>  
#include <SelectMgr_SelectableObject.hxx>  
#include <SelectMgr_Selection.hxx>  
#include <SelectMgr_SelectionManager.hxx>  
#include <SelectMgr_ListOfFilter.hxx>  
#include <SelectMgr_Filter.hxx>  
#include <StdSelect_EdgeFilter.hxx>  
#include <StdSelect_ShapeTypeFilter.hxx>  
#include <Standard_Boolean.hxx>  
#include <Standard_CString.hxx>  
#include <Standard_ErrorHandler.hxx>  
#include <Standard_Integer.hxx>  
#include <Standard_IStream.hxx>  
#include <Standard_Macro.hxx>  
#include <Standard_NotImplemented.hxx>  
#include <Standard_OStream.hxx>  
#include <Standard_Real.hxx>  
#include <StdPrs_Curve.hxx>  
#include <StdPrs_Point.hxx>  
#include <StdPrs_PoleCurve.hxx>  
#include <TCollection_AsciiString.hxx>  
#include <TColgp_Array1OfPnt2d.hxx>  
#include <TColgp_HArray1OfPnt2d.hxx>  
#include <TCollection_AsciiString.hxx>  
#include <TColStd_HSequenceOfTransient.hxx>  
#include <TColStd_MapIteratorOfMapOfTransient.hxx>  
#include <TColStd_MapOfTransient.hxx>  
#include <TopExp_Explorer.hxx>  
#include <TopoDS.hxx>  
#include <TopoDS_Compound.hxx>  
#include <TopoDS_Shape.hxx>  
#include <TopoDS_Solid.hxx>  
#include <TopoDS_Vertex.hxx>  
#include <TopExp.hxx>  
#include <TopTools_HSequenceOfShape.hxx>  
#include <UnitsAPI.hxx>  
#include <V3d_View.hxx>  
#include <V3d_Viewer.hxx>  
#include <WNT_Window.hxx>  
#include <Prs3d_PointAspect.hxx>  
#include <AIS_Point.hxx>  
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <BRep_Tool.hxx>  
#include <BRepAlgoAPI_Fuse.hxx>  
#include <BRepBuilderAPI_MakeEdge.hxx>  
#include <BRepBuilderAPI_MakeFace.hxx>  
#include <BRepBuilderAPI_MakeWire.hxx>  
#include <BRepBuilderAPI_MakeVertex.hxx>  
#include <BRepBuilderAPI_Transform.hxx>  
#include <BRepPrimAPI_MakeCone.hxx>  
#include <BRepPrimAPI_MakeRevol.hxx>  
#include <BRepFilletAPI_MakeFillet.hxx>  
#include <BRepBuilderAPI_Copy.hxx>  
#include <BRepBuilderAPI_MakePolygon.hxx>  
#include <BRepLib.hxx>  
#include <BRepOffsetAPI_MakeThickSolid.hxx>  
#include <BRepOffsetAPI_ThruSections.hxx>  
#include <BRepPrimAPI_MakeCylinder.hxx>  
#include <BRepPrimAPI_MakePrism.hxx>  
#include <BRepPrimAPI_MakeTorus.hxx>  
#include <BRepAlgoAPI_Section.hxx>  
#include <BRepPrimAPI_MakeSphere.hxx>  
#include <BRepFeat_SplitShape.hxx>  
#include <TColgp_HArray1OfPnt.hxx>  
#include <GeomAPI_Interpolate.hxx>  
#include <GC_MakeArcOfCircle.hxx>  
#include <GC_MakeSegment.hxx>  
#include <GC_MakeCircle.hxx>  
#include <GCE2d_MakeSegment.hxx>  
#include <gp.hxx>  
#include <gp_Ax1.hxx>  
#include <gp_Ax2.hxx>  
#include <gp_Ax2d.hxx>  
#include <gp_Dir.hxx>  
#include <gp_Dir2d.hxx>  
#include <gp_Pnt.hxx>  
#include <gp_Pnt2d.hxx>  
#include <gp_Trsf.hxx>  
#include <gp_Vec.hxx>  
#include <Geom_CylindricalSurface.hxx>  
#include <Geom_Plane.hxx>  
#include <Geom_Surface.hxx>  
#include <Geom_TrimmedCurve.hxx>  
#include <Geom2d_Ellipse.hxx>  
#include <Geom2d_TrimmedCurve.hxx>  
#include <TopExp_Explorer.hxx>  
#include <TopoDS.hxx>  
#include <TopoDS_Edge.hxx>  
#include <TopoDS_Face.hxx>  
#include <TopoDS_Wire.hxx>  
#include <TopoDS_Shape.hxx>  
#include <TopoDS_Compound.hxx>  
#include <GCPnts_AbscissaPoint.hxx>  
#include <BRepAdaptor_Curve.hxx>  
#include <GeomLib.hxx>  
#include <GeomConvert_CompCurveToBSplineCurve.hxx>  
#include <TopTools_ListOfShape.hxx>  
#include <TopTools_ListIteratorOfListOfShape.hxx>  
#include <TopTools_DataMapOfShapeInteger.hxx>  
#include <TopTools_DataMapOfShapeReal.hxx>  
#include <TopTools_IndexedDataMapOfShapeAddress.hxx>  
#include <V3d_PositionalLight.hxx>  
#include <V3d_DirectionalLight.hxx>  
#include <V3d_AmbientLight.hxx>  
#include <IGESControl_Controller.hxx>  
#include <IGESControl_Writer.hxx>  
#include <Interface_Static.hxx>  
#include <OpenGl_GraphicDriver.hxx>  
#include <Graphic3d_GraphicDriver.hxx>  
#include "IfcFile.h"
#ifdef USE_IFC4
#include "Ifc4.h"
#define IfcSchema Ifc4
#else
#include "Ifc2x3.h"
#define IfcSchema Ifc2x3
#endif
#include "Kernel.h"
#include "IfcGeomElement.h"
using namespace std;
#endif //PCH_H