/********************************************************************************
** Form generated from reading UI file 'SearchEngine.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHENGINE_H
#define UI_SEARCHENGINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SearchEngineClass
{
public:
    QGridLayout *gridLayout;
    QLineEdit *searchText;
    QPushButton *searchButton;
    QPushButton *regexButton;

    void setupUi(QDialog *SearchEngineClass)
    {
        if (SearchEngineClass->objectName().isEmpty())
            SearchEngineClass->setObjectName(QString::fromUtf8("SearchEngineClass"));
        SearchEngineClass->resize(350, 69);
        SearchEngineClass->setMinimumSize(QSize(350, 69));
        SearchEngineClass->setMaximumSize(QSize(350, 69));
        gridLayout = new QGridLayout(SearchEngineClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        searchText = new QLineEdit(SearchEngineClass);
        searchText->setObjectName(QString::fromUtf8("searchText"));

        gridLayout->addWidget(searchText, 0, 0, 1, 1);

        searchButton = new QPushButton(SearchEngineClass);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));

        gridLayout->addWidget(searchButton, 0, 1, 1, 1);

        regexButton = new QPushButton(SearchEngineClass);
        regexButton->setObjectName(QString::fromUtf8("regexButton"));

        gridLayout->addWidget(regexButton, 0, 2, 1, 1);


        retranslateUi(SearchEngineClass);

        QMetaObject::connectSlotsByName(SearchEngineClass);
    } // setupUi

    void retranslateUi(QDialog *SearchEngineClass)
    {
        SearchEngineClass->setWindowTitle(QCoreApplication::translate("SearchEngineClass", "SearchEngine", nullptr));
        searchText->setPlaceholderText(QCoreApplication::translate("SearchEngineClass", "\350\276\223\345\205\245\346\220\234\347\264\242\351\203\250\345\210\206\346\226\207\346\234\254\357\274\210\350\277\230\345\217\257\346\220\234\347\264\242\346\227\266\351\227\264\357\274\211", nullptr));
        searchButton->setText(QCoreApplication::translate("SearchEngineClass", "\346\231\256\351\200\232\346\220\234\347\264\242", nullptr));
        regexButton->setText(QCoreApplication::translate("SearchEngineClass", "\346\255\243\345\210\231\346\220\234\347\264\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchEngineClass: public Ui_SearchEngineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHENGINE_H
