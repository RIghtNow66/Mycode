#ifndef WIDGETINTERFACE_H
#define WIDGETINTERFACE_H

#include <QString>
#include <QVariant>

class WidgetInterface : public QObject
{
    Q_OBJECT
public:
    explicit WidgetInterface(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~WidgetInterface() = default;

    // 刷新数据
    virtual void refreshData() = 0;

    // 绑定数据
    virtual void bindData(const QString& dataKey, const QVariant& value) = 0;

    // 获取已绑定的数据
    virtual QVariant getBoundData(const QString& dataKey) const = 0;

    // 获取所有绑定的数据索引
    virtual QStringList getAllDataKeys() const = 0;

    // 获取控件ID
    virtual QString getId() const = 0;

    // 获取控件类型
    virtual QString getType() const = 0;
};

#endif // WIDGETINTERFACE_H
