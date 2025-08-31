#ifndef WIDGETSELECTIONWINDOW_H
#define WIDGETSELECTIONWINDOW_H

#include <QWidget>
#include <QDialog>
#include "customwidget.h"

namespace Ui
{
class WidgetSelectionWindow;
}

class WidgetSelectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WidgetSelectionWindow(QWidget *parent = nullptr);
    ~WidgetSelectionWindow() override;

    CustomWidget::WidgetType selectedWidgetType() const;
    QString widgetName() const;

private slots:
    void on_widgetList_itemSelectionChanged();
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::WidgetSelectionWindow *ui;
    CustomWidget::WidgetType m_selectedType;
    void updatePreview();
};

#endif // WIDGETSELECTIONWINDOW_H
