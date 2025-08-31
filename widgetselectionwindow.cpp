#include "widgetselectionwindow.h"
#include "ui_widgetselectionwindow.h"
#include "customwidget.h"
#include <QVBoxLayout>

WidgetSelectionWindow::WidgetSelectionWindow(QWidget *parent)
    : QDialog (parent, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint
                          | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint),
    ui(new Ui::WidgetSelectionWindow), m_selectedType(CustomWidget::Table)
{
    ui->setupUi(this);
    setWindowTitle("选择控件");

    // 初始化控件列表
    ui->widgetList->addItem("表格");
    ui->widgetList->addItem("曲线");
    ui->widgetList->addItem("柱状图");
    ui->widgetList->setCurrentRow(0);

    // 初始化预览
    updatePreview();
}

WidgetSelectionWindow::~WidgetSelectionWindow()
{
    delete ui;
}

CustomWidget::WidgetType WidgetSelectionWindow::selectedWidgetType() const
{
    return m_selectedType;
}

QString WidgetSelectionWindow::widgetName() const
{
    QString name = ui->nameEdit->text().trimmed();
    if (name.isEmpty())
    {
        // 如果未输入名称，使用默认名称
        switch (m_selectedType)
        {
            case CustomWidget::Table: return "表格";
            case CustomWidget::Curve: return "曲线";
            case CustomWidget::BarChart: return "柱状图";
            default: return "控件";
        }
    }
    return name;
}

void WidgetSelectionWindow::on_widgetList_itemSelectionChanged()
{
    int index = ui->widgetList->currentRow();
    if (index >= 0 && index < 3)
    {
        m_selectedType = static_cast<CustomWidget::WidgetType>(index);
        updatePreview();
    }
}

void WidgetSelectionWindow::updatePreview()
{
    // 清空预览区域
    QLayout *layout = ui->previewWidget->layout();
    if (layout)
    {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr)
        {
            delete item->widget();
            delete item;
        }
        delete layout;
    }

    // 创建预览控件
    QVBoxLayout *previewLayout = new QVBoxLayout(ui->previewWidget);
    previewLayout->setContentsMargins(5, 5, 5, 5);

    // 使用临时ID创建预览控件
    CustomWidget *previewWidget = new CustomWidget(m_selectedType, "preview");
    previewWidget->setEnabled(false); // 预览控件不可交互
    //previewLayout->addWidget(previewWidget);//这块有问题，需要用QGraphicsView类型

    ui->previewWidget->setLayout(previewLayout);
}

void WidgetSelectionWindow::on_confirmButton_clicked()
{
    accept(); // 触发QDialog的accept信号
    close();
}

void WidgetSelectionWindow::on_cancelButton_clicked()
{
    close();
}
