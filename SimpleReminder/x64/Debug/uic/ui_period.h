/********************************************************************************
** Form generated from reading UI file 'Period.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERIOD_H
#define UI_PERIOD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_PeriodClass
{
public:

    void setupUi(QDialog *PeriodClass)
    {
        if (PeriodClass->objectName().isEmpty())
            PeriodClass->setObjectName(QString::fromUtf8("PeriodClass"));
        PeriodClass->resize(600, 400);

        retranslateUi(PeriodClass);

        QMetaObject::connectSlotsByName(PeriodClass);
    } // setupUi

    void retranslateUi(QDialog *PeriodClass)
    {
        PeriodClass->setWindowTitle(QCoreApplication::translate("PeriodClass", "Period", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PeriodClass: public Ui_PeriodClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERIOD_H
