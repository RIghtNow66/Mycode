/********************************************************************************
** Form generated from reading UI file 'customdash.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMDASH_H
#define UI_CUSTOMDASH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomDash
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *titleBar;
    QHBoxLayout *horizontalLayout;
    QComboBox *canvasList;
    QPushButton *newCanvasButton;
    QPushButton *addWidgetButton;
    QPushButton *deleteCanvasButton;
    QPushButton *deleteWidgetButton;
    QPushButton *editCanvasButton;
    QSpacerItem *horizontalSpacer;
    QGraphicsView *canvasView;

    void setupUi(QMainWindow *CustomDash)
    {
        if (CustomDash->objectName().isEmpty())
            CustomDash->setObjectName(QString::fromUtf8("CustomDash"));
        CustomDash->resize(1024, 768);
        centralwidget = new QWidget(CustomDash);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleBar = new QWidget(centralwidget);
        titleBar->setObjectName(QString::fromUtf8("titleBar"));
        horizontalLayout = new QHBoxLayout(titleBar);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        canvasList = new QComboBox(titleBar);
        canvasList->setObjectName(QString::fromUtf8("canvasList"));

        horizontalLayout->addWidget(canvasList);

        newCanvasButton = new QPushButton(titleBar);
        newCanvasButton->setObjectName(QString::fromUtf8("newCanvasButton"));

        horizontalLayout->addWidget(newCanvasButton);

        addWidgetButton = new QPushButton(titleBar);
        addWidgetButton->setObjectName(QString::fromUtf8("addWidgetButton"));

        horizontalLayout->addWidget(addWidgetButton);

        deleteCanvasButton = new QPushButton(titleBar);
        deleteCanvasButton->setObjectName(QString::fromUtf8("deleteCanvasButton"));

        horizontalLayout->addWidget(deleteCanvasButton);

        deleteWidgetButton = new QPushButton(titleBar);
        deleteWidgetButton->setObjectName(QString::fromUtf8("deleteWidgetButton"));

        horizontalLayout->addWidget(deleteWidgetButton);

        editCanvasButton = new QPushButton(titleBar);
        editCanvasButton->setObjectName(QString::fromUtf8("editCanvasButton"));

        horizontalLayout->addWidget(editCanvasButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(titleBar);

        canvasView = new QGraphicsView(centralwidget);
        canvasView->setObjectName(QString::fromUtf8("canvasView"));
        canvasView->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);

        verticalLayout->addWidget(canvasView);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 9);
        CustomDash->setCentralWidget(centralwidget);

        retranslateUi(CustomDash);

        QMetaObject::connectSlotsByName(CustomDash);
    } // setupUi

    void retranslateUi(QMainWindow *CustomDash)
    {
        CustomDash->setWindowTitle(QCoreApplication::translate("CustomDash", "CustomDash", nullptr));
        newCanvasButton->setText(QCoreApplication::translate("CustomDash", "\346\226\260\345\273\272\347\224\273\345\270\203", nullptr));
        addWidgetButton->setText(QCoreApplication::translate("CustomDash", "\346\226\260\345\242\236\346\216\247\344\273\266", nullptr));
        deleteCanvasButton->setText(QCoreApplication::translate("CustomDash", "\345\210\240\351\231\244\347\224\273\345\270\203", nullptr));
        deleteWidgetButton->setText(QCoreApplication::translate("CustomDash", " \345\210\240\351\231\244\346\216\247\344\273\266", nullptr));
        editCanvasButton->setText(QCoreApplication::translate("CustomDash", "\347\274\226\350\276\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomDash: public Ui_CustomDash {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMDASH_H
