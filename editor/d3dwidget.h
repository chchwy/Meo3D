#pragma once
#include <QWidget>

class D3DWidget : public QWidget
{
    Q_OBJECT

public:
    D3DWidget(QWidget* parent);
    ~D3DWidget() override;

    QPaintEngine* paintEngine() const override { return nullptr; }

private:
    void update();
};


