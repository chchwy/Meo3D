#include "d3dwidget.h"
#include <QTimer>

D3DWidget::D3DWidget(QWidget* parent) : QWidget(parent)
{
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_NativeWindow, true);

    QTimer* timer = new QTimer(this);
    timer->setInterval(30);
    timer->setTimerType(Qt::PreciseTimer);
    connect(timer, &QTimer::timeout, this, &D3DWidget::update);
}

D3DWidget::~D3DWidget()
{
}

void D3DWidget::update()
{
}
