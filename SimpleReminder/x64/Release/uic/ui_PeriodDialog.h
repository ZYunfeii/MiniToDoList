/********************************************************************************
** Form generated from reading UI file 'PeriodDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERIODDIALOG_H
#define UI_PERIODDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PeriodDialogClass
{
public:
    QGridLayout *gridLayout;
    QLineEdit *periodEdit;
    QPushButton *periodButton;

    void setupUi(QDialog *PeriodDialogClass)
    {
        if (PeriodDialogClass->objectName().isEmpty())
            PeriodDialogClass->setObjectName(QString::fromUtf8("PeriodDialogClass"));
        PeriodDialogClass->resize(250, 69);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PeriodDialogClass->sizePolicy().hasHeightForWidth());
        PeriodDialogClass->setSizePolicy(sizePolicy);
        PeriodDialogClass->setMinimumSize(QSize(250, 69));
        PeriodDialogClass->setMaximumSize(QSize(250, 69));
        gridLayout = new QGridLayout(PeriodDialogClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        periodEdit = new QLineEdit(PeriodDialogClass);
        periodEdit->setObjectName(QString::fromUtf8("periodEdit"));

        gridLayout->addWidget(periodEdit, 1, 0, 1, 1);

        periodButton = new QPushButton(PeriodDialogClass);
        periodButton->setObjectName(QString::fromUtf8("periodButton"));

        gridLayout->addWidget(periodButton, 1, 1, 1, 1);


        retranslateUi(PeriodDialogClass);

        QMetaObject::connectSlotsByName(PeriodDialogClass);
    } // setupUi

    void retranslateUi(QDialog *PeriodDialogClass)
    {
        PeriodDialogClass->setWindowTitle(QCoreApplication::translate("PeriodDialogClass", "PeriodDialog", nullptr));
        periodEdit->setPlaceholderText(QCoreApplication::translate("PeriodDialogClass", "\345\215\225\344\275\215\357\274\210\345\244\251\357\274\211", nullptr));
        periodButton->setText(QCoreApplication::translate("PeriodDialogClass", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PeriodDialogClass: public Ui_PeriodDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERIODDIALOG_H
