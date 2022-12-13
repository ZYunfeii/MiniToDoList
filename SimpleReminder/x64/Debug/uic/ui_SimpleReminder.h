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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimpleReminderClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLabel *total;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QLabel *incompleted;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QLabel *hide;
    QSpacerItem *horizontalSpacer_2;
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
        SimpleReminderClass->setMaximumSize(QSize(500, 329));
        centralWidget = new QWidget(SimpleReminderClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\345\256\213\344\275\223"));
        label->setFont(font);

        horizontalLayout->addWidget(label);

        total = new QLabel(centralWidget);
        total->setObjectName(QString::fromUtf8("total"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        total->setFont(font1);

        horizontalLayout->addWidget(total);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout->addWidget(label_3);

        incompleted = new QLabel(centralWidget);
        incompleted->setObjectName(QString::fromUtf8("incompleted"));
        incompleted->setFont(font1);

        horizontalLayout->addWidget(incompleted);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);

        hide = new QLabel(centralWidget);
        hide->setObjectName(QString::fromUtf8("hide"));
        hide->setFont(font1);

        horizontalLayout->addWidget(hide);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(tableView, 1, 0, 1, 1);

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
        label->setText(QCoreApplication::translate("SimpleReminderClass", "\344\272\213\351\241\271\346\200\273\346\225\260\357\274\232", nullptr));
        total->setText(QCoreApplication::translate("SimpleReminderClass", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("SimpleReminderClass", "\346\234\252\345\256\214\346\210\220\346\225\260", nullptr));
        incompleted->setText(QCoreApplication::translate("SimpleReminderClass", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("SimpleReminderClass", "\351\232\220\350\227\217\346\225\260\351\207\217\357\274\232", nullptr));
        hide->setText(QCoreApplication::translate("SimpleReminderClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimpleReminderClass: public Ui_SimpleReminderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLEREMINDER_H
