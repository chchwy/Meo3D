#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

#include "meoengine.h"
#include "MeoRenderer.h"
#include "d3dwidget.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    ui->centralwidget->setLayout(mainLayout);

    d3dwidget = new D3DWidget(this);
    mainLayout->addWidget(d3dwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent*)
{
    if (!mEngineInitialized)
    {
        mEngine = std::make_unique<MeoEngine>();
        mEngine->init((HWND)d3dwidget->winId(), d3dwidget->width(), d3dwidget->height());
        mEngineInitialized = true;
    }
}

