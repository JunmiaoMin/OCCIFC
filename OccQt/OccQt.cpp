#include "OccQt.h"
#include <QToolBar>
#include <QTreeView>
#include <QMessageBox>
#include <QDockWidget>
#include <QFileDialog>
#include <QStandardPaths>
#ifdef _MSC_VER
#include <QWinTaskbarProgress>
#endif
#include <QProgressDialog>
#include <string>

#include <TopoDS.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>

#include <AIS_Shape.hxx>
#include "IfcFile.h"
#ifdef USE_IFC4
#include "Ifc4.h"
#define IfcSchema Ifc4
#else
#include "Ifc2x3.h"
#define IfcSchema Ifc2x3
#endif
#include "IfcGeomElement.h"
#include <IfcGeomIterator.h>
#include <thread>
OccQt::OccQt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    myOccView = new OccView(this);
#ifdef _MSC_VER
	myWindowsTaskbarButton = new QWinTaskbarButton(this);
	myWindowsTaskbarButton->setWindow(windowHandle());
#endif
	myProgressBar = new QProgressBar(this);
	ui.statusBar->addWidget(myProgressBar);

    setCentralWidget(myOccView);
	connect(ui.action_IFC, SIGNAL(triggered()), this, SLOT(openIfc()));
	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
}

OccQt::~OccQt()
{}

void OccQt::openIfc()
{
    QString fileName = QFileDialog::getOpenFileName(this,
		QString::fromUtf8(u8"打开IFC文件"),
		QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
		QString::fromUtf8(u8"工业基础类(*ifc)"));
	QFileInfo fileInfo(fileName);
	if (fileInfo.exists())
    {
		IfcParse::IfcFile file(fileName.toStdString());
		if (file.good())
		{
#ifdef _MSC_VER
			QWinTaskbarProgress* windowsTaskbarProgress = myWindowsTaskbarButton->progress();//设置进度指示器
			windowsTaskbarProgress->setRange(0, 100);
			windowsTaskbarProgress->show();
#endif
			/*QProgressDialog process(this);
			process.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
			process.setWindowTitle(QString::fromUtf8(u8"解析IFC"));
			process.setLabelText(QString::fromUtf8(u8"解析中.."));
			process.setRange(0, products->size());
			process.setModal(true);
			process.setCancelButtonText(QString::fromUtf8(u8"终止"));
			process.show();*/
			myProgressBar->setRange(0, 100);
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
#ifdef _MSC_VER
					windowsTaskbarProgress->setValue(context_iterator.progress());
#endif
					myProgressBar->setValue(context_iterator.progress());
					//process.setValue(process.value() + 1);
					//QCoreApplication::processEvents();
					//if (process.wasCanceled())break;
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
									myOccView->getContext()->Display(myAISSphere, Standard_False);
								}
							}
						}
					}
				} while (context_iterator.next());
			}
			myProgressBar->reset();
#ifdef _MSC_VER
			windowsTaskbarProgress->reset();
#endif
			myOccView->fitAll();
			QString title = QString("%1 - %2").arg("OccQt").arg(fileInfo.fileName());
			this->setWindowTitle(title);
		}
    }
}

void OccQt::newFile()
{
	myOccView->getContext()->EraseAll(Standard_True);
	this->setWindowTitle("OccQt");
}