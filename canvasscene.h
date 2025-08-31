#ifndef CANVASSCENE_H
#define CANVASSCENE_H

#include <QGraphicsScene>
#include <QString>

class CanvasScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CanvasScene(const QString& id, const QString& name, QObject *parent = nullptr);

    QString getId() const;
    QString getName() const;
    void setName(const QString& name);

private:
    QString m_id;   // 画布ID
    QString m_name; // 画布名称
};

#endif // CANVASSCENE_H
