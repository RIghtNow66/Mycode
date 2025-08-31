/********************************************************************************
** Form generated from reading UI file 'widgetselectionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETSELECTIONWINDOW_H
#define UI_WIDGETSELECTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetSelectionWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *contentWidget;
    QHBoxLayout *horizontalLayout;
    QListWidget *widgetList;
    QWidget *rightWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *previewWidget;
    QGroupBox *configGroupBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *configPlaceholder;
    QWidget *buttonWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QPushButton *confirmButton;

    void setupUi(QWidget *WidgetSelectionWindow)
    {
        if (WidgetSelectionWindow->objectName().isEmpty())
            WidgetSelectionWindow->setObjectName(QString::fromUtf8("WidgetSelectionWindow"));
        WidgetSelectionWindow->resize(600, 556);
        verticalLayout = new QVBoxLayout(WidgetSelectionWindow);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        contentWidget = new QWidget(WidgetSelectionWindow);
        contentWidget->setObjectName(QString::fromUtf8("contentWidget"));
        horizontalLayout = new QHBoxLayout(contentWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widgetList = new QListWidget(contentWidget);
        widgetList->setObjectName(QString::fromUtf8("widgetList"));
        widgetList->setMinimumSize(QSize(120, 0));

        horizontalLayout->addWidget(widgetList);

        rightWidget = new QWidget(contentWidget);
        rightWidget->setObjectName(QString::fromUtf8("rightWidget"));
        verticalLayout_2 = new QVBoxLayout(rightWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        previewWidget = new QWidget(rightWidget);
        previewWidget->setObjectName(QString::fromUtf8("previewWidget"));
        previewWidget->setMinimumSize(QSize(0, 200));
        previewWidget->setStyleSheet(QString::fromUtf8("background-color: #ffffff;\n"
"border: 1px solid #cccccc;"));

        verticalLayout_2->addWidget(previewWidget);

        configGroupBox = new QGroupBox(rightWidget);
        configGroupBox->setObjectName(QString::fromUtf8("configGroupBox"));
        formLayoutWidget = new QWidget(configGroupBox);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(20, 40, 391, 171));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setHorizontalSpacing(0);
        formLayout->setVerticalSpacing(0);
        formLayout->setContentsMargins(0, 0, 0, 0);
        nameLabel = new QLabel(formLayoutWidget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameEdit = new QLineEdit(formLayoutWidget);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameEdit);

        configPlaceholder = new QLabel(formLayoutWidget);
        configPlaceholder->setObjectName(QString::fromUtf8("configPlaceholder"));

        formLayout->setWidget(1, QFormLayout::LabelRole, configPlaceholder);


        verticalLayout_2->addWidget(configGroupBox);


        horizontalLayout->addWidget(rightWidget);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 5);

        verticalLayout->addWidget(contentWidget);

        buttonWidget = new QWidget(WidgetSelectionWindow);
        buttonWidget->setObjectName(QString::fromUtf8("buttonWidget"));
        horizontalLayout_2 = new QHBoxLayout(buttonWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        cancelButton = new QPushButton(buttonWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout_2->addWidget(cancelButton);

        confirmButton = new QPushButton(buttonWidget);
        confirmButton->setObjectName(QString::fromUtf8("confirmButton"));

        horizontalLayout_2->addWidget(confirmButton);


        verticalLayout->addWidget(buttonWidget);

        verticalLayout->setStretch(0, 9);
        verticalLayout->setStretch(1, 1);

        retranslateUi(WidgetSelectionWindow);

        QMetaObject::connectSlotsByName(WidgetSelectionWindow);
    } // setupUi

    void retranslateUi(QWidget *WidgetSelectionWindow)
    {
        WidgetSelectionWindow->setWindowTitle(QCoreApplication::translate("WidgetSelectionWindow", "\351\200\211\346\213\251\346\216\247\344\273\266", nullptr));
        configGroupBox->setTitle(QCoreApplication::translate("WidgetSelectionWindow", " \346\216\247\344\273\266\351\205\215\347\275\256", nullptr));
        nameLabel->setText(QCoreApplication::translate("WidgetSelectionWindow", "\346\216\247\344\273\266\345\220\215\347\247\260:", nullptr));
        configPlaceholder->setText(QCoreApplication::translate("WidgetSelectionWindow", "\346\233\264\345\244\232\351\205\215\347\275\256:", nullptr));
        cancelButton->setText(QCoreApplication::translate("WidgetSelectionWindow", "\345\217\226\346\266\210", nullptr));
        confirmButton->setText(QCoreApplication::translate("WidgetSelectionWindow", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetSelectionWindow: public Ui_WidgetSelectionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETSELECTIONWINDOW_H
