#pragma once

#include <QtWidgets/QMainWindow>
#include <qstandarditemmodel.h>
#include <qaction.h>
#include <qmenu.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QCloseEvent> 
#include <qmessagebox.h>
#include <qdatetime.h>
#include "ui_SimpleReminder.h"

class SimpleReminder : public QMainWindow {
    Q_OBJECT

public:
    SimpleReminder(QWidget *parent = nullptr);
    ~SimpleReminder();

private:
    Ui::SimpleReminderClass* ui_;
    QMenu* rightMenu_;  //ÓÒ¼ü²Ëµ¥
    QAction* addAction_;  
    QAction* deleteAction_; 
    QAction* hideAction_;
    QAction* showAllAction_;
    QStandardItemModel* model_;

    QModelIndex deleteIndex_;
    QSqlDatabase db_;
    QString tableName_;

    struct TodoItem{
        QString thing;
        bool done;
    };

    QVector<TodoItem> hideItemCache_;
    bool hideTag_;

    void addItem(const QString thing, bool done);
    bool dbInit();
    bool insertDB(QString thing, bool done);
    void updateThingsCount();

public slots:
    void clickedRightMenu(const QPoint& pos);  //ÓÒ¼üÐÅºÅ²Ûº¯Êý
    void addActionTriggered();
    void deleteActionTriggered();
    void hideActionTriggered();
    void showAllActionTriggered();
    void doubleClicked(const QModelIndex&);

protected:
    void closeEvent(QCloseEvent* e) override;
};
