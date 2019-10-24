#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "meoengine.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MeoEngine* engine = new MeoEngine;
    delete engine;
}

MainWindow::~MainWindow()
{
    delete ui;
}

