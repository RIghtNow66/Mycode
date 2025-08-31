#include "datarefreshthread.h"
#include "customwidget.h"
#include "widgetinterface.h"
#include <QThread>
#include <QMetaObject>

DataRefreshThread::DataRefreshThread(QObject *parent)
    : QThread(parent), m_activeCanvas(nullptr), m_running(false)
{
}

DataRefreshThread::~DataRefreshThread()
{
    stop();
    wait();
}

void DataRefreshThread::setActiveCanvas(CanvasScene* canvas)
{
    QMutexLocker locker(&m_mutex);
    m_activeCanvas = canvas;
}

void DataRefreshThread::stop()
{
    QMutexLocker locker(&m_mutex);
    m_running = false;
}

void DataRefreshThread::run()
{
    m_running = true;
    while (m_running)
    {
        QMutexLocker locker(&m_mutex);
        if (m_activeCanvas)
        {
            // 遍历画布中的所有控件，调用每个控件的refreshData方法
            foreach (QGraphicsItem *item, m_activeCanvas->items())
            {
                WidgetInterface *widget = dynamic_cast<WidgetInterface*>(item);
                if (widget)
                {
                    QMetaObject::invokeMethod(
                        widget,
                        "refreshData",
                        Qt::QueuedConnection
                        );
                }
            }
        }
        locker.unlock();
        msleep(1000); // 先这样写，后面改成控件的配置项，每个控件自己定义刷新时间
    }
}
