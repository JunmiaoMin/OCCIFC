#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OccQt.h"
#include "OccView.h"
#ifdef WNT
#include <QWinTaskbarButton>
#endif
#include <QProgressBar>

class OccQt : public QMainWindow
{
    Q_OBJECT

public:
    OccQt(QWidget *parent = nullptr);
    ~OccQt();
private slots:
    void openIfc();
    void newFile();

private:
    Ui::OccQtClass ui;
    OccView* myOccView;
#ifdef WNT
    QWinTaskbarButton* myWindowsTaskbarButton;
#endif
    QProgressBar* myProgressBar;
};
