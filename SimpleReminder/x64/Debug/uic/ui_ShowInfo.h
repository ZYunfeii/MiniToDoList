/********************************************************************************
** Form generated from reading UI file 'ShowInfo.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWINFO_H
#define UI_SHOWINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_ShowInfoClass
{
public:
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *ShowInfoClass)
    {
        if (ShowInfoClass->objectName().isEmpty())
            ShowInfoClass->setObjectName(QString::fromUtf8("ShowInfoClass"));
        ShowInfoClass->resize(315, 234);
        gridLayout = new QGridLayout(ShowInfoClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textBrowser = new QTextBrowser(ShowInfoClass);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 0, 1, 1);


        retranslateUi(ShowInfoClass);

        QMetaObject::connectSlotsByName(ShowInfoClass);
    } // setupUi

    void retranslateUi(QDialog *ShowInfoClass)
    {
        ShowInfoClass->setWindowTitle(QCoreApplication::translate("ShowInfoClass", "ShowInfo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowInfoClass: public Ui_ShowInfoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWINFO_H
