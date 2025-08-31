#include "customwidget.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QRandomGenerator>
#include <QtMath>
#include <QMutexLocker>

CustomWidget::CustomWidget(WidgetType type, const QString& id, QGraphicsItem *parent)
    : QGraphicsWidget(parent), m_type(type), m_id(id), m_isResizing(false)
{
    // 测试用，后面去掉
    switch (type)
    {
    case Table:
        m_color = QColor(220, 230, 245); // 浅蓝色
        break;
    case Curve:
        m_color = QColor(245, 230, 220); // 浅橙色
        break;
    case BarChart:
        m_color = QColor(220, 245, 230); // 浅绿色
        break;
    }

    // 设置控件属性
    setFlags(QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
    setMinimumSize(150, 100);
    setPreferredSize(200, 150);
}

QRectF CustomWidget::boundingRect() const
{
    return QRectF(0, 0, size().width(), size().height());
}

//测试用，后面集成了控件库后，换成控件的添加
void CustomWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // 绘制控件背景
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(m_color);
    painter->drawRect(boundingRect());

    // 绘制控件类型名称
    painter->drawText(boundingRect(), Qt::AlignCenter, getTypeName());

    // 绘制选中状态
    if (isSelected())
    {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect().adjusted(0, 0, -1, -1));

        // 绘制缩放区域
        painter->setPen(QPen(Qt::darkGray, 1));
        painter->setBrush(QBrush(Qt::lightGray));
        painter->drawRect(size().width() - RESIZE_AREA,
                          size().height() - RESIZE_AREA,
                          RESIZE_AREA, RESIZE_AREA);
    }
}

void CustomWidget::refreshData()
{
    // 数据刷新，控件自己实现

}

void CustomWidget::bindData(const QString& dataKey, const QVariant& value)
{
    QMutexLocker locker(&m_dataMutex);
    m_boundData[dataKey] = value;
}

QVariant CustomWidget::getBoundData(const QString& dataKey) const
{
    if (m_boundData.contains(dataKey)) {
        return m_boundData[dataKey];
    }
    return QVariant();
}

QStringList CustomWidget::getAllDataKeys() const
{
    return m_boundData.keys();
}

QString CustomWidget::getId() const
{
    return m_id;
}

QString CustomWidget::getType() const
{
    switch (m_type)
    {
    case Table: return "Table";
    case Curve: return "Curve";
    case BarChart: return "BarChart";
    default: return "Unknown";
    }
}

CustomWidget::WidgetType CustomWidget::widgetType() const
{
    return m_type;
}

QString CustomWidget::getTypeName() const
{
    switch (m_type)
    {
    case Table: return "表格";
    case Curve: return "曲线";
    case BarChart: return "柱状图";
    default: return "未知";
    }
}

void CustomWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (isInResizeArea(event->pos()))
    {
        m_isResizing = true;
        setCursor(Qt::SizeFDiagCursor);
    }
    else
    {
        m_lastPos = event->scenePos();
        QGraphicsWidget::mousePressEvent(event);
        setZValue(1); // 选中时置于顶层
    }
}

void CustomWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_isResizing)
    {
        // 处理缩放
        QPointF delta = event->pos() - event->lastPos();
        QSizeF newSize = size() + QSizeF(delta.x(), delta.y());

        // 限制最小尺寸
        if (newSize.width() < minimumWidth())
            newSize.setWidth(minimumWidth());
        if (newSize.height() < minimumHeight())
            newSize.setHeight(minimumHeight());

        setGeometry(QRectF(geometry().topLeft(), newSize));
    }
    else
    {
        // 处理移动
        QPointF newPos = pos() + (event->scenePos() - m_lastPos);
        m_lastPos = event->scenePos();

        qreal x = newPos.x();
        qreal y = newPos.y();
        bool aligned = checkAlignmentWithOtherItems(x, y);

        if (aligned)
        {
            showAlignmentGuidelines();
        }
        else
        {
            clearGuidelines();
        }

        setPos(x, y);

        if (collidesWithOtherItems())
        {
            handleCollisions();
        }
        else
        {
            QGraphicsWidget::mouseMoveEvent(event);
        }
    }
}

void CustomWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_isResizing)
    {
        m_isResizing = false;
        setCursor(Qt::ArrowCursor);
    }
    else
    {
        QGraphicsWidget::mouseReleaseEvent(event);
    }
    clearGuidelines();
}

void CustomWidget::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (isSelected() && isInResizeArea(event->pos()))
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsWidget::hoverMoveEvent(event);
}

bool CustomWidget::isInResizeArea(const QPointF &pos) const
{
    return pos.x() >= size().width() - RESIZE_AREA &&
           pos.y() >= size().height() - RESIZE_AREA;
}

void CustomWidget::showAlignmentGuidelines()
{
    clearGuidelines();

    QGraphicsScene *s = scene();
    if (!s) return;

    QRectF thisRect = sceneBoundingRect();
    qreal thisCenterX = thisRect.center().x();
    qreal thisCenterY = thisRect.center().y();
    qreal thisLeft = thisRect.left();
    qreal thisRight = thisRect.right();
    qreal thisTop = thisRect.top();
    qreal thisBottom = thisRect.bottom();

    QPen guidelinePen(Qt::gray, 1, Qt::DashLine);

    foreach (QGraphicsItem *item, s->items())
    {
        if (item == this || item->type() != CustomWidget::Type) continue;

        CustomWidget *other = static_cast<CustomWidget*>(item);
        QRectF otherRect = other->sceneBoundingRect();

        // 中心X对齐
        if (qAbs(thisCenterX - otherRect.center().x()) < SNAP_THRESHOLD)
        {
            QGraphicsLineItem *line = new QGraphicsLineItem(
                QLineF(thisCenterX, 0, thisCenterX, s->height()), this);
            line->setPen(guidelinePen);
            line->setZValue(-1);
            m_guidelines.append(line);
        }

        // 中心Y对齐
        if (qAbs(thisCenterY - otherRect.center().y()) < SNAP_THRESHOLD)
        {
            QGraphicsLineItem *line = new QGraphicsLineItem(
                QLineF(0, thisCenterY, s->width(), thisCenterY), this);
            line->setPen(guidelinePen);
            line->setZValue(-1);
            m_guidelines.append(line);
        }

        // 左边缘对齐
        if (qAbs(thisLeft - otherRect.left()) < SNAP_THRESHOLD)
        {
            QGraphicsLineItem *line = new QGraphicsLineItem(
                QLineF(thisLeft, 0, thisLeft, s->height()), this);
            line->setPen(guidelinePen);
            line->setZValue(-1);
            m_guidelines.append(line);
        }

        // 右边缘对齐
        if (qAbs(thisRight - otherRect.right()) < SNAP_THRESHOLD)
        {
            QGraphicsLineItem *line = new QGraphicsLineItem(
                QLineF(thisRight, 0, thisRight, s->height()), this);
            line->setPen(guidelinePen);
            line->setZValue(-1);
            m_guidelines.append(line);
        }

        // 上边缘对齐
        if (qAbs(thisTop - otherRect.top()) < SNAP_THRESHOLD)
        {
            QGraphicsLineItem *line = new QGraphicsLineItem(
                QLineF(0, thisTop, s->width(), thisTop), this);
            line->setPen(guidelinePen);
            line->setZValue(-1);
            m_guidelines.append(line);
        }

        // 下边缘对齐
        if (qAbs(thisBottom - otherRect.bottom()) < SNAP_THRESHOLD)
        {
            QGraphicsLineItem *line = new QGraphicsLineItem(
                QLineF(0, thisBottom, s->width(), thisBottom), this);
            line->setPen(guidelinePen);
            line->setZValue(-1);
            m_guidelines.append(line);
        }
    }
}

void CustomWidget::clearGuidelines()
{
    foreach (QGraphicsLineItem *line, m_guidelines)
    {
        scene()->removeItem(line);
        delete line;
    }
    m_guidelines.clear();
}

bool CustomWidget::checkAlignmentWithOtherItems(qreal &x, qreal &y)
{
    if (!scene()) return false;

    bool aligned = false;
    QSizeF thisSize = size();

    foreach (QGraphicsItem *item, scene()->items())
    {
        if (item == this || item->type() != CustomWidget::Type) continue;

        CustomWidget *other = static_cast<CustomWidget*>(item);
        QRectF otherRect = other->sceneBoundingRect();

        // 中心X对齐
        if (qAbs((x + thisSize.width()/2) - otherRect.center().x()) < SNAP_THRESHOLD)
        {
            x = otherRect.center().x() - thisSize.width()/2;
            aligned = true;
        }

        // 中心Y对齐
        if (qAbs((y + thisSize.height()/2) - otherRect.center().y()) < SNAP_THRESHOLD)
        {
            y = otherRect.center().y() - thisSize.height()/2;
            aligned = true;
        }

        // 左边缘对齐
        if (qAbs(x - otherRect.left()) < SNAP_THRESHOLD)
        {
            x = otherRect.left();
            aligned = true;
        }

        // 右边缘对齐
        if (qAbs((x + thisSize.width()) - otherRect.right()) < SNAP_THRESHOLD)
        {
            x = otherRect.right() - thisSize.width();
            aligned = true;
        }

        // 上边缘对齐
        if (qAbs(y - otherRect.top()) < SNAP_THRESHOLD)
        {
            y = otherRect.top();
            aligned = true;
        }

        // 下边缘对齐
        if (qAbs((y + thisSize.height()) - otherRect.bottom()) < SNAP_THRESHOLD)
        {
            y = otherRect.bottom() - thisSize.height();
            aligned = true;
        }
    }

    return aligned;
}

bool CustomWidget::collidesWithOtherItems() const
{
    if (!scene()) return false;

    foreach (QGraphicsItem *item, scene()->items(sceneBoundingRect()))
    {
        if (item != this && item->type() == CustomWidget::Type &&
            collidesWithItem(item))
        {
            return true;
        }
    }
    return false;
}

void CustomWidget::handleCollisions()
{
    if (!scene()) return;

    foreach (QGraphicsItem *item, scene()->items(sceneBoundingRect()))
    {
        if (item != this && item->type() == CustomWidget::Type &&
            collidesWithItem(item))
        {
            moveOtherItemsToAvoidCollision(static_cast<CustomWidget*>(item));
        }
    }
}

void CustomWidget::moveOtherItemsToAvoidCollision(CustomWidget *collidingItem)
{
    if (!collidingItem) return;

    QPointF thisCenter = pos() + QPointF(size().width()/2, size().height()/2);
    QPointF otherCenter = collidingItem->pos() +
                          QPointF(collidingItem->size().width()/2,
                                  collidingItem->size().height()/2);

    QPointF delta = otherCenter - thisCenter;

    qreal moveX = 0;
    qreal moveY = 0;

    if (qAbs(delta.x()) > qAbs(delta.y()))
    {
        // 水平方向移动
        if (delta.x() > 0)
        {
            moveX = (size().width() / 2 + collidingItem->size().width() / 2 + AVOID_DISTANCE) - delta.x();
        }
        else
        {
            moveX = -(size().width() / 2 + collidingItem->size().width() / 2 + AVOID_DISTANCE) - delta.x();
        }
    }
    else
    {
        // 垂直方向移动
        if (delta.y() > 0)
        {
            moveY = (size().height() / 2 + collidingItem->size().height() / 2 + AVOID_DISTANCE) - delta.y();
        }
        else
        {
            moveY = -(size().height() / 2 + collidingItem->size().height() / 2 + AVOID_DISTANCE) - delta.y();
        }
    }

    collidingItem->setPos(collidingItem->pos() + QPointF(moveX, moveY));

    if (collidingItem->collidesWithOtherItems())
    {
        collidingItem->handleCollisions();
    }
}
