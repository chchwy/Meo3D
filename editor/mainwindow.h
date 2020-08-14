#pragma once
#include <QMainWindow>

class D3DWidget;
class MeoEngine;
class QShowEvent;
namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void showEvent(QShowEvent* event) override;

private:
    std::unique_ptr<MeoEngine> mEngine;

    D3DWidget* d3dwidget = nullptr;
    bool mEngineInitialized = false;
    Ui::MainWindow* ui = nullptr;
};
