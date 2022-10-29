#ifndef _OCCVIEW_H_
#define _OCCVIEW_H_

#include <QOpenGLWidget>

#include <AIS_InteractiveContext.hxx>

class QMenu;
class QRubberBand;

//! Adapted a QWidget for OpenCASCADE viewer.
class OccView : public QWidget
{
    Q_OBJECT


public:
    //! constructor.
    OccView(QWidget* parent);

    const Handle(AIS_InteractiveContext)& getContext() const;

signals:
    void selectionChanged(void);

public slots:
    //! operations for the view.
    void fitAll(void);
    void reset(void);

protected:
    virtual QPaintEngine* paintEngine() const;

    // Paint events.
    virtual void paintEvent(QPaintEvent* theEvent);
    virtual void resizeEvent(QResizeEvent* theEvent);

    // Mouse events.
    virtual void mousePressEvent(QMouseEvent* theEvent);
    virtual void mouseReleaseEvent(QMouseEvent* theEvent);
    virtual void mouseMoveEvent(QMouseEvent* theEvent);
    virtual void wheelEvent(QWheelEvent* theEvent);

    // Button events.
    virtual void onLButtonDown(const int theFlags, const QPoint thePoint);
    virtual void onMButtonDown(const int theFlags, const QPoint thePoint);
    virtual void onRButtonDown(const int theFlags, const QPoint thePoint);
    virtual void onMouseWheel(const int theFlags, const int theDelta, const QPoint thePoint);
    virtual void onLButtonUp(const int theFlags, const QPoint thePoint);
    virtual void onMButtonUp(const int theFlags, const QPoint thePoint);
    virtual void onRButtonUp(const int theFlags, const QPoint thePoint);
    virtual void onMouseMove(const int theFlags, const QPoint thePoint);

protected:
    void init(void);
    void dragEvent(const int x, const int y);
    void inputEvent(const int x, const int y);
    void moveEvent(const int x, const int y);
    void multiMoveEvent(const int x, const int y);
    void multiDragEvent(const int x, const int y);
    void multiInputEvent(const int x, const int y);
    void drawRubberBand(const int minX, const int minY, const int maxX, const int maxY);

private:

    //! the occ viewer.
    Handle(V3d_Viewer) myViewer;

    //! the occ view.
    Handle(V3d_View) myView;

    //! the occ context.
    Handle(AIS_InteractiveContext) myContext;

    //! save the mouse position.
    Standard_Integer myXmin;
    Standard_Integer myYmin;
    Standard_Integer myXmax;
    Standard_Integer myYmax;

    //! save the degenerate mode state.
    Standard_Boolean myDegenerateModeIsOn;

    //! rubber rectangle for the mouse selection.
    QRubberBand* myRectBand;

};

#endif // _OCCVIEW_H_
