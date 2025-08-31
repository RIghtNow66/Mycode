#ifndef CUSTOMDASH_H
#define CUSTOMDASH_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QList>
#include "canvasscene.h"
#include "datarefreshthread.h"

namespace Ui
{
    class CustomDash;
}

class CustomDash : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomDash(QWidget *parent = nullptr);
    ~CustomDash() override;

private slots:
    void on_newCanvasButton_clicked();//新建画布
    void on_deleteCanvasButton_clicked();//删除画布
    void on_addWidgetButton_clicked();//新建控件
    void on_deleteWidgetButton_clicked();//删除控件
    void on_editCanvasButton_clicked();//编辑控件
    void on_canvasList_currentIndexChanged(int index);//画布列表选择事件

private:
    Ui::CustomDash *ui;
    QList<CanvasScene*> m_canvases;
    DataRefreshThread* m_refreshThread;

    void setCanvasEditable(bool editable);
    bool m_isEditable; // 是否为编辑模式

    void addCanvas(const QString& name);
    void updateCanvasList();
    CanvasScene* currentCanvas() const;
};

#endif // CUSTOMDASH_H
