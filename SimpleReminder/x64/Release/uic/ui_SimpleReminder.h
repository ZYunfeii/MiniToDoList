/********************************************************************************
** Form generated from reading UI file 'SimpleReminder.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLEREMINDER_H
#define UI_SIMPLEREMINDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimpleReminderClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QTableView *tableView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimpleReminderClass)
    {
        if (SimpleReminderClass->objectName().isEmpty())
            SimpleReminderClass->setObjectName(QString::fromUtf8("SimpleReminderClass"));
        SimpleReminderClass->resize(427, 329);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SimpleReminderClass->sizePolicy().hasHeightForWidth());
        SimpleReminderClass->setSizePolicy(sizePolicy);
        SimpleReminderClass->setMinimumSize(QSize(427, 329));
        SimpleReminderClass->setMaximumSize(QSize(427, 329));
        centralWidget = new QWidget(SimpleReminderClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(tableView, 1, 0, 1, 1);

        SimpleReminderClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SimpleReminderClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 427, 22));
        SimpleReminderClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SimpleReminderClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SimpleReminderClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SimpleReminderClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SimpleReminderClass->setStatusBar(statusBar);

        retranslateUi(SimpleReminderClass);

        QMetaObject::connectSlotsByName(SimpleReminderClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimpleReminderClass)
    {
        SimpleReminderClass->setWindowTitle(QCoreApplication::translate("SimpleReminderClass", "SimpleReminder", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimpleReminderClass: public Ui_SimpleReminderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLEREMINDER_H
