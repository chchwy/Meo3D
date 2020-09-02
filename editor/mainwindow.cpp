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

    mDxWidget = new D3DWidget(this);
    mainLayout->addWidget(mDxWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent*)
{
    if (!mEngine)
    {
        mEngine = std::make_unique<MeoEngine>();
        mEngine->Init((HWND)mDxWidget->winId(), mDxWidget->width(), mDxWidget->height());
        mDxWidget->SetMeoEngine(mEngine.get());
    }
}

