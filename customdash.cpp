#include "customdash.h"
#include "ui_customdash.h"
#include "widgetselectionwindow.h"
#include "customwidget.h"
#include "idgenerator.h"
#include <QInputDialog>
#include <QMessageBox>

CustomDash::CustomDash(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CustomDash), m_refreshThread(new DataRefreshThread(this))
{
    ui->setupUi(this);
    setWindowTitle("CustomDash");

    // 初始化第一个画布
    addCanvas("默认画布");

    // 启动数据刷新线程
    m_refreshThread->start();
}

CustomDash::~CustomDash()
{
    m_refreshThread->stop();
    m_refreshThread->wait();
    delete m_refreshThread;

    // 清理所有画布
    foreach (CanvasScene* canvas, m_canvases)
    {
        delete canvas;
    }
    m_canvases.clear();

    delete ui;
}

void CustomDash::addCanvas(const QString& name)
{
    QString canvasId = IdGenerator::getInstance().generateId("cv");// 生成画布ID，前缀用cv表示

    // 创建新画布
    CanvasScene* canvas = new CanvasScene(canvasId, name);
    m_canvases.append(canvas);

    // 更新画布列表
    updateCanvasList();

    // 如果是第一个画布，设置为当前画布
    if (m_canvases.size() == 1)
    {
        ui->canvasView->setScene(canvas);
        m_refreshThread->setActiveCanvas(canvas);
    }
}

void CustomDash::updateCanvasList()
{
    // 保存当前选中的索引
    int currentIndex = ui->canvasList->currentIndex();
    QString currentId;
    if (currentIndex >= 0 && currentIndex < m_canvases.size())
    {
        currentId = m_canvases[currentIndex]->getId();
    }

    // 重新添加下拉列表
    ui->canvasList->clear();
    foreach (CanvasScene* canvas, m_canvases)
    {
        ui->canvasList->addItem(canvas->getName());
    }

    // 恢复选中状态
    if (!currentId.isEmpty())
    {
        for (int i = 0; i < m_canvases.size(); ++i)
        {
            if (m_canvases[i]->getId() == currentId)
            {
                ui->canvasList->setCurrentIndex(i);
                break;
            }
        }
    }
}

CanvasScene* CustomDash::currentCanvas() const
{
    int index = ui->canvasList->currentIndex();
    if (index >= 0 && index < m_canvases.size())
    {
        return m_canvases[index];
    }
    return nullptr;
}

void CustomDash::on_newCanvasButton_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "新建画布",
                                         "请输入画布名称:", QLineEdit::Normal,
                                         "画布" + QString::number(m_canvases.size() + 1), &ok);

    if (ok && !name.isEmpty())
    {
        addCanvas(name);
    }
}

void CustomDash::on_deleteCanvasButton_clicked()
{
    if (m_canvases.size() <= 1)
    {
        QMessageBox::warning(this, "警告", "至少保留一个画布!");
        return;
    }

    int index = ui->canvasList->currentIndex();
    if (index >= 0 && index < m_canvases.size())
    {
        // 确认删除
        if (QMessageBox::question(this, "确认删除",
                                  QString("确定要删除画布 \"%1\" 吗?")
                                      .arg(m_canvases[index]->getName()),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            CanvasScene* canvas = m_canvases.takeAt(index);
            delete canvas;

            // 更新画布列表
            updateCanvasList();

            // 设置新的当前画布
            if (!m_canvases.isEmpty())
            {
                ui->canvasView->setScene(m_canvases.first());
                m_refreshThread->setActiveCanvas(m_canvases.first());
            }
        }
    }
}

void CustomDash::on_addWidgetButton_clicked()
{
    CanvasScene* canvas = currentCanvas();
    if (!canvas) return;

    // 显示控件选择窗口
    WidgetSelectionWindow dialog(nullptr);
    dialog.setWindowModality(Qt::NonModal); // 非模态窗口
    if (dialog.exec() == QDialog::Accepted)
    {
        // 根据选择的类型生成控件ID
        QString typePrefix;
        switch (dialog.selectedWidgetType())
        {
        case CustomWidget::Table:
            typePrefix = "tb"; // table
            break;
        case CustomWidget::Curve:
            typePrefix = "cu"; // curve
            break;
        case CustomWidget::BarChart:
            typePrefix = "bc"; // bar chart
            break;
        }

        // 生成控件ID
        QString widgetId = IdGenerator::getInstance().generateId(typePrefix);

        // 创建控件
        CustomWidget* widget = new CustomWidget(dialog.selectedWidgetType(), widgetId);

        // 设置控件在画布中心
        QPointF center(canvas->sceneRect().width() / 2 - widget->size().width() / 2,
                       canvas->sceneRect().height() / 2 - widget->size().height() / 2);
        widget->setPos(center);

        // 添加到画布
        canvas->addItem(widget);
    }
}

void CustomDash::on_deleteWidgetButton_clicked()
{
    CanvasScene* canvas = currentCanvas();
    if (!canvas) return;

    // 获取选中的控件
    QList<QGraphicsItem*> selectedItems = canvas->selectedItems();
    if (selectedItems.isEmpty())
    {
        QMessageBox::information(this, "提示", "请先选中要删除的控件!");
        return;
    }

    if (QMessageBox::question(this, "确认删除",
                              QString("确定要删除选中的 %1 个控件吗?")
                                  .arg(selectedItems.size()),
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        foreach (QGraphicsItem* item, selectedItems)
        {
            if (item->type() == CustomWidget::Type)
            {
                canvas->removeItem(item);
                delete item;
            }
        }
    }
}

void CustomDash::on_canvasList_currentIndexChanged(int index)
{
    if (index >= 0 && index < m_canvases.size())
    {
        ui->canvasView->setScene(m_canvases[index]);
        m_refreshThread->setActiveCanvas(m_canvases[index]);
    }
}
