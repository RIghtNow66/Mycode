#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <QString>
#include <QMap>
#include <QMutex>

class IdGenerator
{
public:

    static IdGenerator& getInstance();// 获取单例实例
    QString generateId(const QString& typePrefix);// 生成新ID

    // 禁止复制和赋值
    IdGenerator(const IdGenerator&) = delete;
    IdGenerator& operator=(const IdGenerator&) = delete;

private:

    IdGenerator() = default;
    QMap<QString, int> m_counters; // 每种类型的控件单独计数
    QMutex m_mutex;               // 互斥锁，保证线程安全
};

#endif // IDGENERATOR_H
