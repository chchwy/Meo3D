#include "d3dwidget.h"
#include <chrono>

#include <QTimer>
#include <QDebug>
#include <QResizeEvent>

#include "meoengine.h"


D3DWidget::D3DWidget(QWidget* parent) : QWidget(parent)
{
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_NativeWindow, true);

    QTimer* timer = new QTimer(this);
    timer->setInterval(30);
    timer->setTimerType(Qt::PreciseTimer);
    connect(timer, &QTimer::timeout, this, &D3DWidget::tick);

    timer->start();
}

D3DWidget::~D3DWidget()
{
}

void D3DWidget::SetMeoEngine(MeoEngine* eg)
{
    Q_ASSERT(eg);
    mMeoEngine = eg;
}

void D3DWidget::paintEvent(QPaintEvent* event)
{
    if (mMeoEngine)
    {
        mMeoEngine->Draw();
    }
}

void D3DWidget::resizeEvent(QResizeEvent* event)
{
    if (mMeoEngine)
    {
        mMeoEngine->Resize(event->size().width(), event->size().height());
    }
}

void D3DWidget::tick()
{
    /*
    static long long m1 = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();
    auto m = std::chrono::time_point_cast<std::chrono::microseconds>(t1).time_since_epoch().count();
    qDebug() << "Paint Event!" << double(m - m1) * 0.001;
    m1 = m;
    */
}
