#pragma once

#include <QtWidgets/QMainWindow>
#include <qstandarditemmodel.h>
#include <qaction.h>
#include <qmenu.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QCloseEvent> 
#include <QScrollBar>
#include <QtWidgets/QDesktopWidget>
#include <QSharedMemory>
#include <QTimer>
#include <QDebug>
#include <algorithm>
#include <qmessagebox.h>
#include "ui_SimpleReminder.h"
#include "PeriodDialog.h"
#include "SearchEngine.h"
#include "meta.h"
#include "item.h"

#define TEST_BIT(a, b) a & b
#define HIDE_BORDER 30 //����ʱ��ʾborder
#define CHECK_BORDER 10 //�߽�����
#define EXPIRE_TIMER_INTERVAL 5 // ˢ�¹���ʱ�� ��λ������
#define PERSISTENCE_INTERVAL 1 // �Զ��־û� ��λ������
#define WIDTH_RECORD_1 340
#define WIDTH_RECORD_2 200

#define DBNAME "record.db"

class SimpleReminder : public QMainWindow {
    Q_OBJECT

public:
    SimpleReminder(QWidget *parent = nullptr);
    ~SimpleReminder();

private:
    enum FloatingFeature {
        NoArea = 0x0,
        TopArea = 0x1,
        BottomArea = 0x2,
        LeftArea = 0x4,
        RightArea = 0x8,
        RightAndTopArea = 0x81,
        AllArea = 0xf,
    };

    Ui::SimpleReminderClass* ui_;
    QMenu* rightMenu_;  //�Ҽ��˵�
    QAction* addAction_;  
    QAction* deleteAction_; 
    QAction* hideAction_;
    QAction* showAllAction_;
    QAction* periodAction_;
    QAction* detailAction_;
    QAction* timeShowAction_;
    QAction* searchAction_;
    QStandardItemModel* model_;

    QPoint dragPosition_;
    QPoint recoverPosition_;
    FloatingFeature feature_;
    QTimer* timer_;
    QTimer* expireTimer_;
    QTimer* persistenceTimer_;

    QModelIndex selectedIndex_;
    QSqlDatabase db_;
    QString tableName_;

    PeriodDialog* periodDialog_;
    SearchEngine* searchEngine_;

    QList<TodoItem> hideItemCache_;
    QList<TodoItem> temporaryCache_;
    QVector< QAction*> actionVec_;

    bool isVisable_;
    bool detailTag_;
    bool timeDetailTag_;
    bool modifyTag_; // ���־û������޸ı�ṹΪfalse������Ϊtrue�������ж�closeEventʱ�Ƿ��ٴγ־û�
    bool searchTag_;

    bool dbInit();
    void actionInit();
    void tableInit();
    void timerInit();
    void addItem(TodoItem&& item, int pos = -1);
    bool insertDB(TodoItem&& item);
    void updateThingsCount();
    void updateOrder(int row, bool done); 
    void moveWindow(const QPoint& start, const QPoint& end, unsigned int step = 5);
    void hideAllColumn();
    void showAllColumn();
    void hideTimeColumn();
    void showTimeColumn();
    void copyToTemCache();
    void pullFromTemCache();

public slots:
    void clickedRightMenu(const QPoint& pos);  //�Ҽ��źŲۺ���
    void addActionTriggered();
    void deleteActionTriggered();
    void hideActionTriggered();
    void showAllActionTriggered();
    void periodActionTriggered();
    void detailActionTriggered();
    void timeShowTriggered();
    void searchActionTriggered();
    void doubleClicked(const QModelIndex&);
    void showDockWidget();
    void hideDockWidget();
    void expireUpdate();
    void dataPersistence();

protected:
    void closeEvent(QCloseEvent* e) Q_DECL_OVERRIDE;;
    void mousePressEvent(QMouseEvent* e) Q_DECL_OVERRIDE;;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;;
    void leaveEvent(QEvent* e) Q_DECL_OVERRIDE;;
    void enterEvent(QEvent* e) Q_DECL_OVERRIDE;;
    
};
