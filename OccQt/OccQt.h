#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OccQt.h"
#include "OccView.h"
#ifdef _MSC_VER
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
#ifdef _MSC_VER
    QWinTaskbarButton* myWindowsTaskbarButton;
#endif
    QProgressBar* myProgressBar;
};
