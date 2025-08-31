#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QGraphicsItem>
#include <QGraphicsWidget>
#include <QColor>
#include <QMap>
#include "widgetinterface.h"
#include <QMutex>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QCursor>

class CustomWidget : public WidgetInterface , public QGraphicsWidget
{
    Q_INTERFACES(WidgetInterface)

public:
    enum WidgetType
    {
        Table,
        Curve,
        BarChart
    };

    enum { Type = QGraphicsItem::UserType + 1 };
    int type() const override { return Type; }

    CustomWidget(WidgetType type, const QString& id, QGraphicsItem *parent = nullptr);

    // 从QGraphicsItem继承
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // 从WidgetInterface继承，通用接口各个控件自己实现
    void refreshData() override;
    void bindData(const QString& dataKey, const QVariant& value) override;
    QVariant getBoundData(const QString& dataKey) const override;
    QStringList getAllDataKeys() const override;
    QString getId() const override;
    QString getType() const override;

    // 自定义方法
    WidgetType widgetType() const;
    QString getTypeName() const;

protected:
    // 鼠标事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    bool isInResizeArea(const QPointF &pos) const;//检测是否在缩放区域
    void showAlignmentGuidelines();//显示辅助线
    void clearGuidelines();//清除辅助线
    bool checkAlignmentWithOtherItems(qreal &x, qreal &y);//对齐
    bool collidesWithOtherItems() const;//碰撞检测
    void handleCollisions();//处理碰撞
    void moveOtherItemsToAvoidCollision(CustomWidget *collidingItem);//避让逻辑

    WidgetType m_type;          // 控件类型
    QString m_id;               // 控件ID
    QColor m_color;             // 控件颜色
    bool m_isResizing;          // 是否正在缩放
    QPointF m_lastPos;          // 上一位置
    QList<QGraphicsLineItem*> m_guidelines; // 辅助线列表
    QMap<QString, QVariant> m_boundData;    // 绑定的数据
    QMutex m_dataMutex; // 数据保护互斥锁

    static const int RESIZE_AREA = 10;      // 缩放区域大小
    static const int SNAP_THRESHOLD = 5;    // 吸附阈值
    static const int AVOID_DISTANCE = 10;   // 避让距离
};

#endif // CUSTOMWIDGET_H
