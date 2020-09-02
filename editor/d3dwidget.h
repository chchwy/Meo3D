#pragma once
#include <QWidget>


class MeoEngine;

class D3DWidget : public QWidget
{
    Q_OBJECT

public:
    D3DWidget(QWidget* parent);
    ~D3DWidget() override;

    QPaintEngine* paintEngine() const override { return nullptr; }

    void SetMeoEngine(MeoEngine*);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void tick();

    MeoEngine* mMeoEngine = nullptr;
};


