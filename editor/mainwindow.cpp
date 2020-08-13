#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

#include "meoengine.h"
#include "d3dwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    ui->centralwidget->setLayout(mainLayout);

    D3DWidget* d3dwidget = new D3DWidget(this);
    mainLayout->addWidget(d3dwidget);

    //MeoEngine* engine = new MeoEngine;
    //delete engine;
}

MainWindow::~MainWindow()
{
    delete ui;
}

