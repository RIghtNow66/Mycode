#include "canvasscene.h"

CanvasScene::CanvasScene(const QString& id, const QString& name, QObject *parent)
    : QGraphicsScene(parent), m_id(id), m_name(name)
{
    // 设置大小
    setSceneRect(0, 0, 1000, 800);

    // 绘制边框
    addRect(sceneRect(), QPen(Qt::darkGray, 1));
}

QString CanvasScene::getId() const
{
    return m_id;
}

QString CanvasScene::getName() const
{
    return m_name;
}

void CanvasScene::setName(const QString& name)
{
    m_name = name;
}
