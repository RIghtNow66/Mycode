#include "idgenerator.h"

IdGenerator& IdGenerator::getInstance()
{
    static IdGenerator instance;
    return instance;
}

QString IdGenerator::generateId(const QString& typePrefix)
{
    QMutexLocker locker(&m_mutex);

    // 第一次则初始化
    if (!m_counters.contains(typePrefix))
    {
        m_counters[typePrefix] = 1;
    }

    // 生成ID：前缀 + 三位数序号
    QString id = QString("%1%2").arg(typePrefix)
                     .arg(m_counters[typePrefix], 3, 10, QChar('0'));

    // 计数器递增
    m_counters[typePrefix]++;

    return id;
}
