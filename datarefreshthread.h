#ifndef DATAREFRESHTHREAD_H
#define DATAREFRESHTHREAD_H

#include <QThread>
#include <QMutex>
#include "canvasscene.h"

class DataRefreshThread : public QThread
{
    Q_OBJECT

public:
    explicit DataRefreshThread(QObject *parent = nullptr);
    ~DataRefreshThread() override;

    void setActiveCanvas(CanvasScene* canvas);
    void stop();

protected:
    void run() override;

private:
    QMutex m_mutex;
    CanvasScene* m_activeCanvas;
    bool m_running;
};

#endif // DATAREFRESHTHREAD_H
